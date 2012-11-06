/*
 * COIStation.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "COIStation.h"

namespace ccoifits
{

COIStation::COIStation(string telescope_name, string station_name, int station_index, float diameter, valarray<double> xyz)
{
	this->tel_name = telescope_name;
	this->sta_name = station_name;
	this->sta_index = station_index;
	this->diameter = diameter;
	this->xyz = xyz;
}

COIStation::~COIStation()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
