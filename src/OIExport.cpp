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

using namespace std;

namespace ccoifits
{

/// Directly exports all data contained in data to the output valarrays and attempts to minimize the
/// total number of UV points in the data set.
///
/// To find the uv point of

//void MinUVExport(const OIDataList & data, vector<pair<double,double> > & uv_points,
//		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err, vector<unsigned int> vis_uv_ref,
//		valarray<double> & vis2, valarray<double> & vis2_err, vector<unsigned int> vis2_uv_ref,
//		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err, vector<vector<unsigned int>> t3_uv_ref, vector<vector<int> > t3_uv_sign)
//{
//	// First call direct export to get the raw data out
//	vector<pair<double,double> > t_uv;
//	vector<unsigned int> t_uv_ref;
//	vector<unsigned int> t_uv_sign;
//
//	DirectExport(data, t_uv, vis, vis_err, vis2, vis2_err, t3, t3_err);
//
//
//}

/// Directly exports all data contained in data to the output valarrays
/// Indexing of uv_points is to be understood as:
///		uv_points[0 ... N(vis) - 1] are for vis
///		uv_points[N(vis) ... N(vis) + N(vis2) - 1] are for v2
///		uv_points[N(vis) + N(vis2) ... N(vis) + N(vis2) + 3*N(t3) - 1] are for T3
///	where the t3 data UV points are in strides of three (i.e. [uv_ab, uv_bc, uv_ca])
/// All data that is not flagged will be exported. uv_points is not simplified
/// or intelligently filtered in any way.
//void DirectExport(const OIDataList & data, vector<pair<double,double> > & uv_points,
//		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err,
//		valarray<double> & vis2, valarray<double> & vis2_err,
//		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err)
//{
//	// First split data into three sublists:
//	OIDataList t_vis = FilterByDataType(data, COIDataRow::OI_VIS);
//	OIDataList t_vis2 = FilterByDataType(data, COIDataRow::OI_VIS2);
//	OIDataList t_t3 = FilterByDataType(data, COIDataRow::OI_T3);
//
////	DirectExport(t_vis, uv_points, vis, vis_err);
//	DirectExport(t_vis2, uv_points, vis2, vis2_err);
//	DirectExport(t_t3, uv_points, t3, t3_err);
//}
//
///// A helper function for exporting data. Specialized for COIV2Row records
//void DirectExport(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<double> & data, valarray<double> & data_err)
//{
//	OIDataRowPtr row;
//	COIV2Row * vis2_row;
//	unsigned int t_n_data = 0;
//	vector<double> wavelengths;
//
//	// Allocate room in the data arrays:
//	int n_rows = data_list.size();
//	int n_data = CountActiveData(data_list);
//
//	data.resize(n_data);
//	data_err.resize(n_data);
//
//	// Now iterate through the data_list, exporting the UV points and data to the output arrays.
//	// 	i is the row counter
//	// 	j is the output data index
//	for(int i = 0, j = 0; i < n_rows; i++)
//	{
//		// For convenience, rename a few things:
//		row = data_list[i];
//		t_n_data = row->GetMaskedNData();
//		wavelengths = row->GetMaskedWavelengths();
//
//		// Generate and push_back scaled UV coordinates
//		for(auto wavelength : wavelengths)
//		{
//			for(auto uv : row->mUV)
//				uv_points.push_back(uv->GetScaledPair(wavelength));
//		}
//
//		// Now copy over the data:
//		vis2_row = dynamic_cast<COIV2Row*>(row.get());
//		if(vis2_row != NULL)
//		{
//			data[slice(j, t_n_data, 1)] = vis2_row->GetMaskedData();
//		}
//
//		// Increment the output array counter
//		j += t_n_data;
//	}
//}
//
///// A helper function for exporting data. Specialized for COIT3DataRow and COIVisDataRow records.
//void DirectExport(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<complex<double>> & data, valarray<complex<double>> & data_err)
//{
//	OIDataRowPtr row;
////	COIVisRow * vis_row;
//	COIT3Row * t3_row;
//	unsigned int t_n_data = 0;
//	vector<double> wavelengths;
//
//	// Allocate room in the data arrays:
//	int n_rows = data_list.size();
//	int n_data = 0;
//	for(auto row : data_list)
//		n_data += row->GetMaskedNData();
//
//	data.resize(n_data);
//	data_err.resize(n_data);
//
//	// Now iterate through the data_list, exporting the UV points and data to the output arrays.
//	// 	i is the row counter
//	// 	j is the output data index
//	for(int i = 0, j = 0; i < n_rows; i++)
//	{
//		// For convenience, rename a few things:
//		row = data_list[i];
//		t_n_data = row->GetMaskedNData();
//		wavelengths = row->GetMaskedWavelengths();
//
//		// Generate and push_back scaled UV coordinates
//		for(auto wavelength : wavelengths)
//		{
//			for(auto uv : row->mUV)
//				uv_points.push_back(uv->GetScaledPair(wavelength));
//		}
//
//		// Now copy over the data:
//		t3_row = dynamic_cast<COIT3Row*>(row.get());
//		if(t3_row != NULL)
//		{
//			data[slice(j, t_n_data, 1)] = t3_row->GetMaskedData();
//
//		}
//
//		// Increment the output array counter
//		j += t_n_data;
//	}
//}

} /* namespace ccoifits */
