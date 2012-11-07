/*
 * OI_VIS2.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "OI_VIS2.h"
#include "COIV2Row.h"
#include "COIFile.h"

namespace ccoifits
{

OI_VIS2::OI_VIS2(ExtHDU & table, COIFile * parent)
:	OI_DATA_TABLE(table)
{
	// Verify that we have an OI_VIS2 table
	if(mTable.name() != "OI_VIS2")
		throw;

	mParent = parent;
}

OI_VIS2::~OI_VIS2()
{
	// TODO Auto-generated destructor stub
}

OIDataList OI_VIS2::read()
{
	// Read in the common data:
	vector<int> target_ids;
	vector<double> times;
	vector<double> MJDs;
	vector<double> int_times;
	vector< valarray<int> > sta_indicies;
	vector< valarray<bool> > flags;
	OI_DATA_TABLE::ReadCommon(target_ids, times, MJDs, int_times, sta_indicies, flags);

	// Now read in the V2-specific columns:
	int n_rows = mTable.rows();
	vector< valarray<double> > v2_data = ReadArray<double>("VIS2DATA");
	vector< valarray<double> > v2_data_err = ReadArray<double>("VIS2ERR");

	vector<double> ucoord = ReadColumn<double>("UCOORD");
	vector<double> vcoord = ReadColumn<double>("VCOORD");

	// Now create and store V2 objects:
	vector<OIDataRowPtr> output;

	OIArrayPtr array = mParent->GetArray(this->GetArrayName());
	OIWavelengthPtr wave = mParent->GetWavelength(this->GetInstrumentName());

	for(int i = 0; i < n_rows; i++)
	{
		OITargetPtr target = mParent->GetTarget(target_ids[i]);

		OIUVPtr uv( new COIUV(ucoord[i], vcoord[i]));

		OIDataRowPtr tmp( new COIV2Row(target, array, wave, times[i], MJDs[i], int_times[i], sta_indicies[i], flags[i], uv, v2_data[i], v2_data_err[i]) );
		output.push_back(tmp);
	}

	return output;
}


} /* namespace ccoifits */
