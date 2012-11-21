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

using namespace std;

namespace ccoifits
{

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

class UVKDTree;
class kd_uv_node;
typedef shared_ptr<kd_uv_node> node_ptr;

void Export_Direct(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<pair<double,double>> & vis_err,
		valarray<double> & vis2, valarray<double> & vis2_err,
		valarray<complex<double>> & t3, valarray<pair<double,double>> & t3_err);

void Export_Direct_V2(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<double> & data, valarray<double> & data_err);
void Export_Direct_T3(const OIDataList & data_list, vector<pair<double,double> > & uv_points, valarray<complex<double>> & data, valarray<pair<double,double>> & data_err);

void Export_MinUV(const OIDataList & data, vector<pair<double,double> > & uv_points,
		valarray<complex<double>> & vis, valarray<pair<double,double>> & vis_err, vector<unsigned int> & vis_uv_ref,
		valarray<double> & vis2, valarray<double> & vis2_err, vector<unsigned int> & vis2_uv_ref,
		valarray<complex<double>> & t3, valarray<pair<double,double>> & t3_err,
		vector<tuple<unsigned int, unsigned int, unsigned int>> & t3_uv_ref,
		vector<tuple<short, short, short>> & t3_uv_sign);
void Export_MinUV_V2(UVKDTree & uv_tree, const OIDataList & data_list, vector<node_ptr> & uv_points, valarray<double> & data, valarray<double> & data_err);
void Export_MinUV_T3(UVKDTree & uv_tree, const OIDataList & data_list, vector<tuple<node_ptr, node_ptr, node_ptr> > & uv_refs,
		valarray<complex<double>> & data, valarray<pair<double,double>> & data_err,
		vector<tuple<short, short, short>> & uv_sign);

} /* namespace ccoifits */
#endif /* OIEXPORT_H_ */
