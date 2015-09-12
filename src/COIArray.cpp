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

COIArray::	COIArray(const string & array_name, const string &  frame,
		const vector<double> & xyz, const vector<OIStationPtr> & stations)
	: m_array_name(array_name),
	  m_frame(frame),
	  m_xyz(xyz),
	  m_stations(stations)
{
}

COIArray::~COIArray()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
