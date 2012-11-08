/*
 * OI_VIS2.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "OI_T3.h"
#include "COIT3Row.h"
#include "COIFile.h"

namespace ccoifits
{

OI_T3::OI_T3(ExtHDU & table, COIFile * parent)
:	OI_DATA_TABLE(table)
{
	// Verify that we have an OI_VIS2 table
	if(mTable.name() != "OI_T3")
		throw;

	mParent = parent;
}

OI_T3::~OI_T3()
{
	// TODO Auto-generated destructor stub
}

OIDataList OI_T3::read()
{
	// Read in the common data:
	vector<int> target_ids;
	vector<double> times;
	vector<double> MJDs;
	vector<double> int_times;
	vector< valarray<int> > sta_indicies;
	vector< valarray<bool> > flags;
	OI_DATA_TABLE::ReadCommon(target_ids, times, MJDs, int_times, sta_indicies, flags);

	// Now read in the T3-specific columns:
	int n_rows = mTable.rows();
	vector< valarray<double> > t3_amp = ReadArray<double>("T3AMP");
	vector< valarray<double> > t3_phi = ReadArray<double>("T3PHI");
	vector< valarray<double> > t3_amp_err = ReadArray<double>("T3AMPERR");
	vector< valarray<double> > t3_phi_err = ReadArray<double>("T3PHIERR");

	// Copy the data into valarrays of complex doubles for storage in the COIT3Row class;
	vector< valarray< complex<double> > > data;
	vector< valarray< complex<double> > > data_err;

	int n_cols = 0;
	if(n_rows > 0)	// This could be false if someone created a OI_T3 table with no data in it.
		n_cols = t3_amp[0].size();

	for(int i = 0; i < n_rows; i++)
	{
		// Create a new valarray to store the data values:
		valarray< complex<double> > temp(n_cols);
		valarray< complex<double> > temp_err(n_cols);

		// Fill
		for(int j = 0; j < n_cols; j++)
		{
			temp[j] = complex<double>(t3_amp[i][j], t3_phi[i][j]);
			temp_err[j] = complex<double>(t3_amp_err[i][j], t3_phi_err[i][j]);
		}

		// Push them onto the vector.
		data.push_back(temp);
		data_err.push_back(temp_err);
	}

	// TODO: UV Points!
	// Read in the UV points (UV 31 is implicitly defined)
	vector<double> ucoord1 = ReadColumn<double>("U1COORD");
	vector<double> vcoord1 = ReadColumn<double>("V1COORD");
	vector<double> ucoord2 = ReadColumn<double>("U2COORD");
	vector<double> vcoord2 = ReadColumn<double>("V2COORD");

	// Now create and store T3 objects:
	vector<OIDataRowPtr> output;

	OIArrayPtr array = mParent->GetArray(this->GetArrayName());
	OIWavelengthPtr wave = mParent->GetWavelength(this->GetInstrumentName());

	for(int i = 0; i < n_rows; i++)
	{
		OITargetPtr target = mParent->GetTarget(target_ids[i]);

		OIUVPtr uv12( new COIUV(ucoord1[i], vcoord1[i]));
		OIUVPtr uv23( new COIUV(ucoord2[i], vcoord2[i]));

		OIDataRowPtr tmp( new COIT3Row(target, array, wave, times[i], MJDs[i], int_times[i], sta_indicies[i], flags[i], uv12, uv23, data[i], data_err[i]) );
		output.push_back(tmp);
	}

	return output;
}


} /* namespace ccoifits */