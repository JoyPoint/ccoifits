/*
 * COIStation.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "COIStation.h"

namespace ccoifits
{

COIStation::COIStation(const string & telescope_name, const string &  station_name,
		int station_index, float diameter, const valarray<double> & xyz)
: m_tel_name(telescope_name), m_sta_name(station_name),
  m_sta_index(station_index), m_diameter(diameter), m_xyz(xyz)
{
}

COIStation::~COIStation()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
