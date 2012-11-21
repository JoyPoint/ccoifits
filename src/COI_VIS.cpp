/*
 * OI_VIS2.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "COI_VIS.h"
#include "COIVisRow.h"
#include "oi_file.hpp"

#ifndef PI
#include <cmath>
#define PI M_PI
#endif // PI

namespace ccoifits
{

COI_VIS::COI_VIS(ExtHDU & table, COIFile * parent)
:	COI_DATA_TABLE(table)
{
	// Verify that we have an OI_VIS2 table
	if(mTable.name() != "OI_VIS")
		throw;

	mParent = parent;
}

COI_VIS::~COI_VIS()
{
	// TODO Auto-generated destructor stub
}

OIDataList COI_VIS::read()
{
	// Read in the common data:
	vector<int> target_ids;
	vector<double> times;
	vector<double> MJDs;
	vector<double> int_times;
	vector< valarray<int> > sta_indicies;
	vector< valarray<bool> > flags;
	COI_DATA_TABLE::ReadCommon(target_ids, times, MJDs, int_times, sta_indicies, flags);

	// Now read in the V2-specific columns:
	int n_rows = mTable.rows();
	vector< valarray<double> > vis_amp = ReadArray<double>("VISAMP");
	vector< valarray<double> > vis_phi = ReadArray<double>("VISPHI");
	vector< valarray<double> > vis_amp_err = ReadArray<double>("VISAMPERR");
	vector< valarray<double> > vis_phi_err = ReadArray<double>("VISPHIERR");

	vector<double> ucoord = ReadColumn<double>("UCOORD");
	vector<double> vcoord = ReadColumn<double>("VCOORD");

	// Now create and store V2 objects:
	vector<OIDataRowPtr> output;

	OIArrayPtr array = mParent->GetArray(this->GetArrayName());
	OIWavelengthPtr wave = mParent->GetWavelength(this->GetInstrumentName());

	int n_cols = 0;
	if(n_rows > 0)	// This could be false if someone created a OI_T3 table with no data in it.
		n_cols = vis_amp[0].size();

	double real = 0;
	double imag = 0;
	for(int i = 0; i < n_rows; i++)
	{
		OITargetPtr target = mParent->GetTarget(target_ids[i]);
		OIUVPtr uv( new COIUV(ucoord[i], vcoord[i]));

		// Create a new valarray to store the data values:
		valarray< complex<double> > temp(n_cols);
		valarray< pair<double,double> > temp_err(n_cols);

		// Fill in the data
		for(int j = 0; j < n_cols; j++)
		{
			// Create a new valarray to store the data values:
			real = vis_amp[i][j] * cos(vis_phi[i][j] * PI/180);
			imag = vis_amp[i][j] * sin(vis_phi[i][j] * PI/180);
			temp[j] = complex<double>(real, imag);
			temp_err[j] = pair<double,double>(vis_amp_err[i][j], vis_phi_err[i][j] * PI/180);
		}

		OIDataRowPtr tmp( new COIVisRow(target, array, wave, times[i], MJDs[i], int_times[i], sta_indicies[i], flags[i], uv, temp, temp_err) );
		output.push_back(tmp);
	}

	return output;
}


} /* namespace ccoifits */
