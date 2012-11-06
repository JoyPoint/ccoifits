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
	string tel_name;
	string sta_name;
	int sta_index;
	float diameter;
	valarray<double> xyz;

public:
	COIStation(string telescope_name, string station_name, int station_index, float diameter, valarray<double> xyz);
	virtual ~COIStation();
};

} /* namespace ccoifits */
#endif /* COISTATION_H_ */
