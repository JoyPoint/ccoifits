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

/// Directly exports all data contained in data to the output valarrays
/// Indexing of uv_points is to be understood as:
///		uv_points[0 ... N(vis) - 1] are for vis
///		uv_points[N(vis) ... N(vis2) - 1] are for v2
///		uv_points[N(vis2) ... 3*N(t3) - 1] are for T3
///	where the t3 data are in strides of three (i.e. [uv_ab, uv_bc, uv_ca])
/// All data that is not flagged will be exported. uv_points is not simplified
/// or intelligently filtered in any way.
void DirectExport(OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err,
		valarray<double> & vis2, valarray<double> & vis2_err,
		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err)
{
	// First split data into three sublists:
	OIDataList t_vis = FilterByDataType(data, COIDataRow::OI_VIS);
	OIDataList t_vis2 = FilterByDataType(data, COIDataRow::OI_VIS2);
	OIDataList t_t3 = FilterByDataType(data, COIDataRow::OI_T3);

	// Now go through each list and extract the data.
}

} /* namespace ccoifits */
