/*
 * OIDATATABLE.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "OI_DATA_TABLE.h"

namespace ccoifits
{

OI_DATA_TABLE::OI_DATA_TABLE(ExtHDU & table)
: OI_TABLE(table)
{

}

OI_DATA_TABLE::~OI_DATA_TABLE()
{

}

string OI_DATA_TABLE::GetDateObs()
{
	return ReadKey<string>("DATE-OBS");
}

string OI_DATA_TABLE::GetArrayName()
{
	return ReadKey<string>("ARRNAME");
}

string OI_DATA_TABLE::GetInstrumentName()
{
	return ReadKey<string>("INSNAME");
}

/// Reads in an array of all data that is common in the base class.  This includes:
/// TARGET_ID, TIME, MJD, INT_TIME, STA_INDEX, FLAG
void OI_DATA_TABLE::ReadCommon(vector<int> & target_ids, vector<double> & times, vector<double> & MJDs, vector<double> & int_times, vector< valarray<int> > & sta_indicies, vector< valarray<bool> > & flags)
{
	target_ids = ReadColumn<int>("TARGET_ID");
	times = ReadColumn<double>("TIME");
	MJDs = ReadColumn<double>("MJD");
	int_times = ReadColumn<double>("INT_TIME");
	sta_indicies = ReadArray<int>("STA_INDEX");
	flags = ReadArray<bool>("FLAG");
}

} /* namespace ccoifits */
