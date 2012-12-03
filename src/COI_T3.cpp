/*
 * OI_VIS2.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "COI_T3.h"
#include "COIT3Row.h"
#include "oi_file.hpp"

#include <limits>

using namespace std;

#ifndef PI
#include <cmath>
#define PI M_PI
#endif // PI

namespace ccoifits
{

COI_T3::COI_T3(ExtHDU & table, COIFile * parent)
:	COI_DATA_TABLE(table)
{
	// Verify that we have an OI_VIS2 table
	if(mTable.name() != "OI_T3")
		throw;

	mParent = parent;
}

COI_T3::~COI_T3()
{
	// TODO Auto-generated destructor stub
}

OIDataList COI_T3::read()
{
	// Read in the common data:
	vector<int> target_ids;
	vector<double> times;
	vector<double> MJDs;
	vector<double> int_times;
	vector< valarray<int> > sta_indicies;
	vector< valarray<bool> > flags;
	COI_DATA_TABLE::ReadCommon(target_ids, times, MJDs, int_times, sta_indicies, flags);

	// Now read in the T3-specific columns:
	int n_rows = mTable.rows();
	vector< valarray<double> > t3_amp = ReadArray<double>("T3AMP");
	vector< valarray<double> > t3_phi = ReadArray<double>("T3PHI");
	vector< valarray<double> > t3_amp_err = ReadArray<double>("T3AMPERR");
	vector< valarray<double> > t3_phi_err = ReadArray<double>("T3PHIERR");

	// Copy the data into valarrays of complex doubles for storage in the COIT3Row class;
	vector< valarray< complex<double> > > data;
	vector< valarray< pair<double,double> > > data_err;

	int n_cols = 0;
	if(n_rows > 0)	// This could be false if someone created a OI_T3 table with no data in it.
		n_cols = t3_amp[0].size();

	// Now copy the data into complex data fields
	double real = 0;
	double imag = 0;
	for(int i = 0; i < n_rows; i++)
	{
		// Create a new valarray to store the data values:
		valarray< complex<double> > temp(n_cols);
		valarray< pair<double,double> > temp_err(n_cols);

		// Fill in the data
		for(int j = 0; j < n_cols; j++)
		{
			// If the phase has not been calibrated, the amplitude will be NULL.
			// In this case, we still form the data products, but set the amplitude
			// error to infinity.
			if(std::isnan(t3_amp[i][j]))
			{
				// Set T3 amp = 1, use phase only.
				real = cos(t3_phi[i][j] * PI/180);
				imag = sin(t3_phi[i][j] * PI/180);
				temp[j] = complex<double>(real, imag);
				temp_err[j] = pair<double,double>(numeric_limits<double>::max(), t3_phi_err[i][j] * PI/180);

			}
			else
			{
				real = t3_amp[i][j] * cos(t3_phi[i][j] * PI/180);
				imag = t3_amp[i][j] * sin(t3_phi[i][j] * PI/180);
				temp[j] = complex<double>(real, imag);
				temp_err[j] = pair<double,double>(t3_amp_err[i][j], t3_phi_err[i][j]  * PI/180);
			}
		}

		// Push them onto the vector.
		data.push_back(temp);
		data_err.push_back(temp_err);
	}

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
