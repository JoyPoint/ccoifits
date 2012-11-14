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
#include <memory>

#include "COIDataRow.h"

using namespace std;

namespace ccoifits
{

void Export_Direct(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err,
		valarray<double> & vis2, valarray<double> & vis2_err,
		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err);

void Export_Direct(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<double> & data, valarray<double> & data_err);
void Export_Direct(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<complex<double>> & data, valarray<complex<double>> & data_err);

void Export_MinUV(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<complex<double>> & vis_err, vector<unsigned int> & vis_uv_ref,
		valarray<double> & vis2, valarray<double> & vis2_err, vector<unsigned int> & vis2_uv_ref,
		valarray<complex<double>> & t3, valarray<complex<double>> & t3_err,
		vector<tuple<unsigned int, unsigned int, unsigned int>> & t3_uv_ref,
		vector<tuple<short, short, short>> & t3_uv_sign);

} /* namespace ccoifits */
#endif /* OIEXPORT_H_ */
