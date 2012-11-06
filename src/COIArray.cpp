/*
 * COIArray.cpp
 *
 *  Created on: Nov 6, 2012
 *      Author: bkloppen
 */

#include "COIArray.h"
#include "COIStation.h"

namespace ccoifits
{

COIArray::	COIArray(string array_name, string frame, vector<double> xyz, vector<OIStationPtr> stations)
{
	this->array_name = array_name;
	this->frame = frame;
	this->xyz = xyz;
	this->stations = stations;
}

COIArray::~COIArray()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
