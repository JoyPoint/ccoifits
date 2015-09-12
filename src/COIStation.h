/*
 * COIStation.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef COISTATION_H_
#define COISTATION_H_

#include <valarray>
#include <vector>
#include <memory>
#include <string>

using namespace std;

namespace ccoifits
{

class COIStation;
typedef shared_ptr<COIStation> StationPtr;

class COIStation
{
public:
	string m_tel_name;
	string m_sta_name;
	int m_sta_index;
	float m_diameter;
	valarray<double> m_xyz;

public:
	COIStation(const string & telescope_name, const string &  station_name,
			int station_index, float diameter, const valarray<double> & xyz);
	virtual ~COIStation();
};

} /* namespace ccoifits */
#endif /* COISTATION_H_ */
