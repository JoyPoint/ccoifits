/*
 * OIExport.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#include "OIExport.h"

#include <vector>
#include <complex>
#include <valarray>

#include "COIDataRow.h"
#include "COIV2Row.h"
#include "COIT3Row.h"
#include "OIFilter.h"
#include "OITools.h"

using namespace std;

namespace ccoifits
{

/// Directly exports all data contained in data to the output valarrays and attempts to minimize the
/// total number of UV points in the data set.
///
/// To find the uv point of

void Export_MinUV(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err, vector<unsigned int> vis_uv_ref,
		valarray<double> & vis2, valarray<double> & vis2_err, vector<unsigned int> vis2_uv_ref,
		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err,
		vector<tuple<unsigned int, unsigned int, unsigned int>> & t3_uv_ref,
		vector<tuple<short, short, short>> & t3_uv_sign)
{
	// First call direct export to get the raw data out
	vector<pair<double,double> > t_uv;
	vector<unsigned int> t_uv_ref;
	vector<unsigned int> t_uv_sign;

	Export_Direct(data, t_uv, vis, vis_err, vis2, vis2_err, t3, t3_err);

	// TODO: This is an O(N^2) operation.  We should be able to do this in O(N log(N)) (at worst) using a kd-tree

	// Now minimize the number of UV points. We compare every uv point in t_uv to the output array, uv_points.
	// We also keep track of any conjugation that needs to happen.
	for(int i = 0; i < uv_points.size(); i++)
	{
		int j = 0;
		int match = 0;	// takes values {-1, 0, 1}
		for(; j < t_uv.size() && match == 0; j++)
			match = COIUV::compare_uv(t_uv[j], uv_points[i]);

		// No match found
		if(match == 0)
		{
			uv_points.push_back(t_uv[i]);
			t_uv_ref.push_back(uv_points.size());
			t_uv_sign.push_back(1);
		}
		else
		{
			t_uv_ref.push_back(j);
			t_uv_sign.push_back(match);
		}
	}

	// Now set the *_uv_ref and sign values
	// First OI_VIS:
	int offset = 0;
	for(int i = 0; i < vis.size(); i++)
	{
		vis_uv_ref.push_back(t_uv_ref[i]);
	}

	// Next OI_VIS2
	offset = vis.size();
	for(int i = 0; i < vis2.size(); i++)
	{
		vis2_uv_ref.push_back(t_uv_ref[offset + i]);
	}

	// Lastly OI_T3.  Remember we need signs here too.
	offset = vis.size() + vis2.size();
	for(int i = 0; i < t3.size(); i++)
	{
		tuple<unsigned int, unsigned int, unsigned int> uv_refs(t_uv_ref[offset + 3*i], t_uv_ref[offset + 3*i + 1], t_uv_ref[offset + 3*i + 2]);
		t3_uv_ref.push_back(uv_refs);

		tuple<short, short, short> signs(t_uv_sign[offset + 3*i], t_uv_sign[offset + 3*i + 1], t_uv_sign[offset + 3*i + 2]);
		t3_uv_sign.push_back(signs);
	}
}

/// Directly exports all data contained in data to the output valarrays
/// Indexing of uv_points is to be understood as:
///		uv_points[0 ... N(vis) - 1] are for vis
///		uv_points[N(vis) ... N(vis) + N(vis2) - 1] are for v2
///		uv_points[N(vis) + N(vis2) ... N(vis) + N(vis2) + 3*N(t3) - 1] are for T3
///	where the t3 data UV points are in strides of three (i.e. [uv_ab, uv_bc, uv_ca])
/// All data that is not flagged will be exported. uv_points is not simplified
/// or intelligently filtered in any way.
void Export_Direct(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err,
		valarray<double> & vis2, valarray<double> & vis2_err,
		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err)
{
	// First split data into three sublists:
	OIDataList t_vis = FilterByDataType(data, COIDataRow::OI_VIS);
	OIDataList t_vis2 = FilterByDataType(data, COIDataRow::OI_VIS2);
	OIDataList t_t3 = FilterByDataType(data, COIDataRow::OI_T3);

//	DirectExport(t_vis, uv_points, vis, vis_err);
	Export_Direct(t_vis2, uv_points, vis2, vis2_err);
	Export_Direct(t_t3, uv_points, t3, t3_err);
}

/// A helper function for exporting data. Specialized for COIV2Row records
void Export_Direct(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<double> & data, valarray<double> & data_err)
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
		}

		// Increment the output array counter
		j += t_n_data;
	}
}

/// A helper function for exporting data. Specialized for COIT3DataRow and COIVisDataRow records.
void Export_Direct(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<complex<double>> & data, valarray<complex<double>> & data_err)
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

		}

		// Increment the output array counter
		j += t_n_data;
	}
}

} /* namespace ccoifits */
