/*
 * OIExport.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#include "oi_export.hpp"

#include <vector>
#include <complex>
#include <valarray>
#include <stdexcept>
#include <string>
#include <fstream>

#ifndef PI
#include <cmath>
#define PI M_PI
#endif // PI

#include "COIDataRow.h"
#include "COIV2Row.h"
#include "COIT3Row.h"
#include "oi_filter.hpp"
#include "oi_tools.hpp"
#include "UVKDTree.h"

using namespace std;

namespace ccoifits
{

/// Directly exports all data contained in data to the output valarrays
/// Indexing of uv_points is to be understood as:
///		uv_points[0 ... N(vis) - 1] are for vis
///		uv_points[N(vis) ... N(vis) + N(vis2) - 1] are for v2
///		uv_points[N(vis) + N(vis2) ... N(vis) + N(vis2) + 3*N(t3) - 1] are for T3
///	where the t3 data UV points are in strides of three (i.e. [uv_ab, uv_bc, uv_ca]).
/// All data that is not flagged will be exported. uv_points is not simplified
/// or intelligently filtered in any way.
void Export_Direct(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<pair<double,double> > & vis_err,
		valarray<double> & vis2, valarray<double> & vis2_err,
		valarray<complex<double>> & t3, valarray<pair<double,double>> & t3_err)
{
	// First split data into three sublists:
	OIDataList t_vis;
	OIDataList t_vis2;
	OIDataList t_t3;
	FilterByDataType(data, t_vis, t_vis2, t_t3);

//	DirectExport(t_vis, uv_points, vis, vis_err);
	Export_Direct_V2(t_vis2, uv_points, vis2, vis2_err);
	Export_Direct_T3(t_t3, uv_points, t3, t3_err);
}

/// A helper function for exporting data. Specialized for COIV2Row records
void Export_Direct_V2(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<double> & data, valarray<double> & data_err)
{
	OIDataRowPtr row;
	COIV2Row * vis2_row;
	unsigned int t_n_data = 0;
	vector<double> wavelengths;

	// Allocate room in the data arrays:
	int n_rows = data_list.size();
	int n_data = CountActiveData(data_list);

	data.resize(n_data);
	data_err.resize(n_data);

	// Now iterate through the data_list, exporting the UV points and data to the output arrays.
	// 	i is the row counter
	// 	j is the output data index
	for(int i = 0, j = 0; i < n_rows; i++)
	{
		// For convenience, rename a few things:
		row = data_list[i];
		t_n_data = row->GetMaskedNData();
		wavelengths = row->GetMaskedWavelengths();

		// Generate and push_back scaled UV coordinates
		for(auto wavelength : wavelengths)
		{
			for(auto uv : row->mUV)
				uv_points.push_back(uv->GetScaledPair(wavelength));
		}

		// Now copy over the data:
		vis2_row = dynamic_cast<COIV2Row*>(row.get());
		if(vis2_row != NULL)
		{
			data[slice(j, t_n_data, 1)] = vis2_row->GetMaskedData();
			data_err[slice(j, t_n_data, 1)] = vis2_row->GetMaskedDataError();
		}

		// Increment the output array counter
		j += t_n_data;
	}
}

/// A helper function for exporting data. Specialized for COIT3DataRow and COIVisDataRow records.
void Export_Direct_T3(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<complex<double>> & data, valarray<pair<double,double>> & data_err)
{
	OIDataRowPtr row;
//	COIVisRow * vis_row;
	COIT3Row * t3_row;
	unsigned int t_n_data = 0;
	vector<double> wavelengths;

	// Allocate room in the data arrays:
	int n_rows = data_list.size();
	int n_data = 0;
	for(auto row : data_list)
		n_data += row->GetMaskedNData();

	data.resize(n_data);
	data_err.resize(n_data);

	// Now iterate through the data_list, exporting the UV points and data to the output arrays.
	// 	i is the row counter
	// 	j is the output data index
	for(int i = 0, j = 0; i < n_rows; i++)
	{
		// For convenience, rename a few things:
		row = data_list[i];
		t_n_data = row->GetMaskedNData();
		wavelengths = row->GetMaskedWavelengths();

		// Generate and push_back scaled UV coordinates
		for(auto wavelength : wavelengths)
		{
			for(auto uv : row->mUV)
				uv_points.push_back(uv->GetScaledPair(wavelength));
		}

		// Now copy over the data:
		t3_row = dynamic_cast<COIT3Row*>(row.get());
		if(t3_row != NULL)
		{
			data[slice(j, t_n_data, 1)] = t3_row->GetMaskedData();
			data_err[slice(j, t_n_data, 1)] = t3_row->GetMaskedDataError();
		}

		// Increment the output array counter
		j += t_n_data;
	}
}

/// Directly exports all data contained in data to the output valarrays and attempts to minimize the
/// total number of UV points in the data set.
void Export_MinUV(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<pair<double,double> > & vis_err, vector<unsigned int> & vis_uv_ref,
		valarray<double> & vis2, valarray<double> & vis2_err, vector<unsigned int> & vis2_uv_ref,
		valarray<complex<double>> & t3, valarray<pair<double,double>> & t3_err,
		vector<tuple<unsigned int, unsigned int, unsigned int>> & t3_uv_ref,
		vector<tuple<short, short, short>> & t3_uv_sign)
{
	// To minimize the number of UV points, we first insert the UV points into a KD-tree. To avoid
	// unnecessary parsing, we build the initial tree with only UV points from Vis, V2, or T3 data.
	// We then find the UV points for the Vis, V2, and T3 data, keeping track of sign changes
	// whenever necessary.

	// First split data into three sublists:
	OIDataList t_vis;
	OIDataList t_vis2;
	OIDataList t_t3;
	vector<node_ptr> t_vis_ref;
	vector<node_ptr> t_v2_ref;
	vector<tuple<node_ptr, node_ptr, node_ptr>> t_t3_ref;
	FilterByDataType(data, t_vis, t_vis2, t_t3);

	// Normally there are visibilities or V2s at locations where T3s (or T4s) exist, so we are
	// going to try to exploit this property.
	UVKDTree uv_tree;
	if(t_vis.size() > 0)
		uv_tree.BuildTree(t_vis);
	else if(t_vis2.size() > 0)
		uv_tree.BuildTree(t_vis2);
	else if(t_t3.size() > 0)
		uv_tree.BuildTree(t_t3);
	else
		throw runtime_error("ccoifits::Export_MinUV: No data found!");

	// We should now have a nearly balanced tree of UV points.  Now lets start exporting data.
	// In the ideal case where every T3/V2 has a matching V2/Vis record, the tree should not
	// change in size.
//	cout << "Tree Size " << uv_tree.size() << endl;
//	cout << "Inserting OI_VIS records" << endl;
//	Export_MinUV_Vis(uv_tree, t_vis, t_vis_ref, vis, vis_err);
//	cout << "N(Vis) " << t_vis.size() << endl;
//	cout << "Vis uv_ref size " << t_vis_ref.size() << endl;
//	cout << "Tree Size " << uv_tree.size() << endl;
//
//	cout << "Inserting OI_VIS2 records" << endl;
	Export_MinUV_V2(uv_tree, t_vis2, t_v2_ref, vis2, vis2_err);
//	cout << "N(V2) " << t_vis2.size() << endl;
//	cout << "V2 uv_ref size " << t_v2_ref.size() << endl;
//	cout << "Tree Size " << uv_tree.size() << endl;

//	cout << "Inserting OI_T3 records" << endl;
	Export_MinUV_T3(uv_tree, t_t3, t_t3_ref, t3, t3_err, t3_uv_sign);
//	cout << "N(T3) " << t_t3.size() << endl;
//	cout << "T3 uv_ref size (1/3 total T3 records)" << t_t3_ref.size() << endl;
//	cout << "Tree Size " << uv_tree.size() << endl;

	// Now that all of the data has been exported and any additional UV points inserted
	// flatten out the UV tree so we may resolve the order of the uv points.
	uv_tree.AssignIndicies();
	uv_points = uv_tree.Flatten();

	// Resolve out the node_ptr->node_index => array position.
	for(auto node : t_vis_ref)
		vis_uv_ref.push_back(node->index);

	for(auto node : t_v2_ref)
		vis2_uv_ref.push_back(node->index);

	for(auto triplet : t_t3_ref)
		t3_uv_ref.push_back( make_tuple(get<0>(triplet)->index, get<1>(triplet)->index, get<2>(triplet)->index) );
}

/// A helper function for exporting data. Specialized for COIV2Row records
void Export_MinUV_V2(UVKDTree & uv_tree, const OIDataList & data_list, vector<node_ptr> & uv_points, valarray<double> & data, valarray<double> & data_err)
{
	OIDataRowPtr row;
	COIV2Row * vis2_row;
	unsigned int t_n_data = 0;
	vector<double> wavelengths;

	// Allocate room in the data arrays:
	int n_rows = data_list.size();
	int n_data = CountActiveData(data_list);

	data.resize(n_data);
	data_err.resize(n_data);

	// Now iterate through the data_list, exporting the UV points and data to the output arrays.
	// 	i is the row counter
	// 	j is the output data index
	for(int i = 0, j = 0; i < n_rows; i++)
	{
		// For convenience, rename a few things:
		row = data_list[i];
		t_n_data = row->GetMaskedNData();
		wavelengths = row->GetMaskedWavelengths();

		// Generate and push_back scaled UV coordinates
		for(auto wavelength : wavelengths)
		{
			for(auto uv : row->mUV)
			{
				uv_points.push_back( uv_tree.FindUV(uv->GetScaledPair(wavelength), true) );
			}
		}

		// Now copy over the data:
		vis2_row = dynamic_cast<COIV2Row*>(row.get());
		if(vis2_row != NULL)
		{
			data[slice(j, t_n_data, 1)] = vis2_row->GetMaskedData();
			data_err[slice(j, t_n_data, 1)] = vis2_row->GetMaskedDataError();
		}

		// Increment the output array counter
		j += t_n_data;
	}
}

/// A helper function for exporting data. Specialized for COIT3DataRow records.
void Export_MinUV_T3(UVKDTree & uv_tree, const OIDataList & data_list, vector<tuple<node_ptr, node_ptr, node_ptr> > & uv_refs,
		valarray<complex<double>> & data, valarray<pair<double,double>> & data_err,
		vector<tuple<short, short, short>> & uv_sign)
{
	OIDataRowPtr row;
//	COIVisRow * vis_row;
	COIT3Row * t3_row;
	unsigned int t_n_data = 0;
	vector<double> wavelengths;
	uv_point scaled_uv;
	valarray<short> sign(3);
	valarray<node_ptr> uv_ref(3);

	// Allocate room in the data arrays:
	int n_rows = data_list.size();
	int n_data = 0;
	for(auto row : data_list)
		n_data += row->GetMaskedNData();

	data.resize(n_data);
	data_err.resize(n_data);

	// Now iterate through the data_list, exporting the UV points and data to the output arrays.
	// 	i is the row counter
	// 	j is the output data index
	for(int i = 0, j = 0; i < n_rows; i++)
	{
		// For convenience, rename a few things:
		row = data_list[i];
		t_n_data = row->GetMaskedNData();
		wavelengths = row->GetMaskedWavelengths();

		// Generate and push_back scaled UV coordinates
		for(auto wavelength : wavelengths)
		{
			for(int k = 0; k < 3; k++)
			{
				auto uv = row->mUV[k];
				sign[k] = 1;

				scaled_uv = uv->GetScaledPair(wavelength);

				// As the KD tree enforces U > 0, we can assign
				// sign like this.
				if(scaled_uv.first < 0)
				{
					scaled_uv.first *= -1;
					scaled_uv.second *= -1;
					sign[k] = -1;
				}

				uv_ref[k] = uv_tree.FindUV(scaled_uv, true);
			}

			uv_refs.push_back(make_tuple(uv_ref[0], uv_ref[1], uv_ref[2]));
			uv_sign.push_back(make_tuple(sign[0], sign[1], sign[2]));
		}

		// Now copy over the data:
		t3_row = dynamic_cast<COIT3Row*>(row.get());
		if(t3_row != NULL)
		{
			data[slice(j, t_n_data, 1)] = t3_row->GetMaskedData();
			data_err[slice(j, t_n_data, 1)] = t3_row->GetMaskedDataError();
		}

		// Increment the output array counter
		j += t_n_data;
	}
}

/// Exports an OIDataList to a series of text files whose names begin with base_filename.
/// The extensions and formats are described in the other Export_ToText function below.
void Export_ToText(const OIDataList & data, string base_filename)
{
	// Get the current OpenCL values:
	vector<pair<double,double> > uv_points;
	valarray<complex<double>> vis;
	valarray<pair<double,double>> vis_err;
	vector<unsigned int> vis_uv_ref;
	valarray<double> vis2;
	valarray<double> vis2_err;
	vector<unsigned int> vis2_uv_ref;
	valarray<complex<double>> t3;
	valarray<pair<double,double> > t3_err;
	vector<tuple<unsigned int, unsigned int, unsigned int>> t3_uv_ref;
	vector<tuple<short, short, short>> t3_uv_sign;

	// Get the data in minimum UV point format:
	Export_MinUV(data, uv_points, vis, vis_err, vis_uv_ref, vis2, vis2_err, vis2_uv_ref, t3, t3_err, t3_uv_ref, t3_uv_sign);
	Export_ToText(base_filename, uv_points, vis, vis_err, vis_uv_ref, vis2, vis2_err, vis2_uv_ref, t3, t3_err, t3_uv_ref, t3_uv_sign);
}

/// Exports the specified data to a series of text files whose names begin with base_filename.
/// Extensions and formats are as follows:
///  *_vis.txt for vis data in "u, v, |uv|, vis_amp, vis_phi, vis_amp_err, vis_phi_err" per line
///  *_v2.txt for V2 data in "u, v, |uv|, v2, v2_err" per line
///  *_t3.txt for T3 data in "u1, v1, u2, v2, u3, v3, |uv|, t3_amp, t3_amp_err, t3_phi, t3_phi_err" per line

void Export_ToText(string base_filename,
	vector<pair<double,double> > uv_points,
	valarray<complex<double>> vis,
	valarray<pair<double,double>> vis_err,
	vector<unsigned int> vis_uv_ref,
	valarray<double> vis2,
	valarray<double> vis2_err,
	vector<unsigned int> vis2_uv_ref,
	valarray<complex<double>> t3,
	valarray<pair<double,double> > t3_err,
	vector<tuple<unsigned int, unsigned int, unsigned int>> t3_uv_ref,
	vector<tuple<short, short, short>> t3_uv_sign)
{

	int n_uv = 0;
	double u1, u2, u3;
	double v1, v2, v3;
	ofstream outfile;
	vector<double> temp;

	// Open the file, write the visibility data
	if(vis.size() > 0)
	{
		outfile.open(base_filename + "_vis.txt");
		outfile << "# File format:" << endl;
		outfile << "# u, v, |u^2+v^2|, vis_amp, vis_phi, vis_amp_err, vis_phi_err" << endl;
		for(unsigned int i = 0; i < vis.size(); i++)
		{
			temp.clear();
			u1 = uv_points[vis_uv_ref[i]].first;
			v1 = uv_points[vis_uv_ref[i]].second;
			temp.push_back(u1);
			temp.push_back(v1);
			temp.push_back(sqrt(u1*u1 + v1*v1));
			temp.push_back(real(vis[i]));
			temp.push_back(imag(vis[i]));
			temp.push_back(vis_err[i].first);
			temp.push_back(vis_err[i].second);

			// Write the output
			outfile << join(",", temp) << endl;
		}
		outfile.close();
	}

	// Now do the V2 data:
	if(vis2.size() > 0)
	{
		outfile.open(base_filename + "_v2.txt");
		outfile << "# File format:" << endl;
		outfile << "# u, v, |u^2+v^2|, v2, v2_err" << endl;
		for(unsigned int i = 0; i < vis2.size(); i++)
		{
			temp.clear();
			u1 = uv_points[vis2_uv_ref[i]].first;
			v1 = uv_points[vis2_uv_ref[i]].second;
			temp.push_back(u1);
			temp.push_back(v1);
			temp.push_back(sqrt(u1*u1 + v1*v1));
			temp.push_back(vis2[i]);
			temp.push_back(vis2_err[i]);

			// Write the output
			outfile << join(",", temp) << endl;
		}
		outfile.close();
	}

	// Lastly, the T3 data:
	if(t3.size() > 0)
	{
		outfile.open(base_filename + "_t3.txt");
		outfile << "# File format:" << endl;
		outfile << "# u1, v1, u2, v2, u3, v3, |u1^2+v1^2+u2^2+v2^2+u3^2+v3^2|, t3_amp, t3_amp_err, t3_phi, t3_phi_err" << endl;
		for(unsigned int i = 0; i < t3.size(); i++)
		{
			temp.clear();
			u1 = uv_points[get<0>(t3_uv_ref[i])].first;
			v1 = uv_points[get<0>(t3_uv_ref[i])].second;
			u2 = uv_points[get<1>(t3_uv_ref[i])].first;
			v2 = uv_points[get<1>(t3_uv_ref[i])].second;
			u3 = uv_points[get<2>(t3_uv_ref[i])].first;
			v3 = uv_points[get<2>(t3_uv_ref[i])].second;
			temp.push_back(u1);
			temp.push_back(v1);
			temp.push_back(u2);
			temp.push_back(v2);
			temp.push_back(u3);
			temp.push_back(v3);
			temp.push_back(sqrt(u1*u1 + v1*v1 + u2*u2 + v2*v2 + u3*u3 + v3*v3));
			temp.push_back(abs(t3[i]));
			temp.push_back(t3_err[i].first);
			// Convert from radians back to degrees (to match OIFITS specifications)
			temp.push_back(arg(t3[i]) * 180 / PI);
			temp.push_back(t3_err[i].second  * 180 / PI);
			// Write the output
			outfile << join(",", temp) << endl;

			// increment the UV counter
			n_uv += 3;
		}
		outfile.close();
	}

}

} /* namespace ccoifits */
