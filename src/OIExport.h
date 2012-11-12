/*
 * OIExport.h
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 *
 * Several functions that are useful when exporting OIDataLists
 */

#ifndef OIEXPORT_H_
#define OIEXPORT_H_

#include <vector>
#include <valarray>
#include <complex>
#include <cassert>

class COIV2Row;
class COIT3Row;

using namespace std;

namespace ccoifits
{

void DirectExport(OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err,
		valarray<double> & vis2, valarray<double> & vis2_err,
		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err);

} /* namespace ccoifits */
#endif /* OIEXPORT_H_ */
