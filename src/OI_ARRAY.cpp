/*
 * COIArray.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "OI_ARRAY.h"
#include "COIArray.h"
#include "COIStation.h"

namespace ccoifits
{

OI_ARRAY::OI_ARRAY(ExtHDU & table)
: OI_TABLE(table)
{

}

OI_ARRAY::~OI_ARRAY()
{
	// TODO Auto-generated destructor stub
}

OIArrayPtr OI_ARRAY::read()
{
	string array_name = ReadKey<string>("ARRNAME");
	string frame = ReadKey<string>("FRAME");
	vector<double> xyz = ReadXYZ();
	vector<OIStationPtr> stations = ReadStations();

	// Now create an OIStationPtr and return it
	OIArrayPtr tmp(new COIArray(array_name, frame, xyz, stations));
	return tmp;
}


vector<double> OI_ARRAY::ReadXYZ()
{
	// init memory. vector of three elements all set to zero.
	vector<double> xyz (3, 0);

	xyz[0] = ReadKey<double>("ARRAYX");
	xyz[1] = ReadKey<double>("ARRAYY");
	xyz[2] = ReadKey<double>("ARRAYZ");

	return xyz;
}

/// Read in the stations from the OIFITS file.
vector<OIStationPtr> OI_ARRAY::ReadStations()
{
	vector<OIStationPtr> stations;

	int n_rows = mTable.rows();
	vector<string> tel_names = ReadColumn<string>("TEL_NAME");
	vector<string> sta_names = ReadColumn<string>("STA_NAME");
	vector<int> sta_index = ReadColumn<int>("STA_INDEX");
	vector<float> diameters = ReadColumn<float>("DIAMETER");

	for(int i = 0; i < n_rows; i++)
	{
		valarray<double> xyz = ReadCells<double>("STAXYZ", i);
		OIStationPtr tmp( new COIStation(tel_names[i], sta_names[i], sta_index[i], diameters[i], xyz) );
		stations.push_back(tmp);
	}

	return stations;
}

} /* namespace ccoifits */
