/*
 * OIExport.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#include "OIExport.h"
#include "OIFilter.h"
#include "COIDataRow.h"

namespace ccoifits
{

/// Exports data stored in an OIDataList into a series of valarrays while minimizing
/// the total number of UV points.
///
/// The data formats are as follows:
///		uv is vector< pair<double, double> > with each entry to be interpreted as (u,v)
///		vis and vis_err are arrays of complex<double>
///		vis2 and vis2_err are arrays of doubles
///		t3 and t3_err are arrays of complex<double>
///
void GetData_MinUV(const OIDataList & data,
		vector< pair<double, double> > & uv,
		valarray<complex<double>> & vis,	valarray<complex<double>> & vis_err, 	valarray<unsigned int> & vis_uv_ref,
		valarray<double> & vis2, 			valarray<double> & vis2_err, 			valarray<unsigned int> & v2_uv_ref,
		valarray<complex<double>> & t3, 	valarray<complex<double>> & t3_err, 	valarray<unsigned int> & t3_uv_ref)
{
	// Objectives:
	//  * Export OI_VIS as an array of double[].  Every 2*i will be a pair (e.g. {real, imag}_0, ... , {real_imag}_n)
	//  * Export OI_VIS2 and errors as arrays of double[]
	//	* Export OI_T3 and errors as arrays of double[].  Every 2*i will be a pair (e.g. {real, imag}_0, ... , {real_imag}_n)
	//	* Export the minimum number of UV points (i.e. V2 and T3 data with the same UV coordinates components should
	//		refer to the same UV point
	//	* Export a "UV reference" array for lookups
	//  * Conjugate all UV points into the +u +v plane

	OIDataList V2 = FilterByDataType(data, COIDataRow::OI_VIS2);
	OIDataList T3 = FilterByDataType(data, COIDataRow::OI_T3);

	// First determine how many V2 and T3 points we will have
	unsigned int n_v2 = 0;
	for(auto vis2_row : V2)
		n_v2 += vis2_row->GetNData();

	unsigned int n_t3 = 0;
	for(auto t3_row : T3)
		n_t3 += t3_row->GetNData();

	// Allocate room for the data
	vis2.resize(n_v2);
	vis2_err.resize(n_v2);
	t3.resize(2*n_t3);
	t3_err.resize(2*n_t3);

	// Copy

	// Lastly copy out the UV points
	int n_uv = uv.size();
	for(int i = 0; i < n_uv; i++)
	{

	}
}

} /* namespace ccoifits */
