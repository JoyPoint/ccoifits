/*
 * OITools.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#include "OITools.h"

#include <random>
#include <chrono>
#include <cmath>
using namespace std;

#include "COIFile.h"
#include "oi_filter.hpp"
#include "COIWavelength.h"
#include "COIDataRow.h"
#include "COIV2Row.h"
#include "COIT3Row.h"
#include "COICalibrator.h"

namespace ccoifits
{

/// Computes the average MJD in the specified OIDataList.
double AverageMJD(const OIDataList & data)
{
	// TODO: Doing it this way probably introduces an overflow bug.  There is a way to
	// avoid it, but I don't recall what it is at this moment.

	long double ave_mjd = 0;
	for(auto row: data)
		ave_mjd += row->mjd;

	if(data.size() > 0)
		return ave_mjd / data.size();

	return -1;
}

/// Creates a data set suitable for bootstrapping by randomly selecting Vis, V2, and T3 data
/// from the original set.  The total number of each of Vis, V2, and T3 is conserved.
/// As flags are modified, this function returns a copy of the underlying data structures.
OIDataList Bootstrap_Random(const OIDataList & data)
{
	// Init the output and random number generator:
	OIDataList output;

	OIDataList temp = FilterByDataType(data, COIDataRow::OI_VIS);
	Bootstrap_Random_Helper(temp, output);

	temp = FilterByDataType(data, COIDataRow::OI_VIS2);
	Bootstrap_Random_Helper(temp, output);

	temp = FilterByDataType(data, COIDataRow::OI_T3);
	Bootstrap_Random_Helper(temp, output);

	return output;
}

/// Function that does the random bootstrapping on data subtypes.
void Bootstrap_Random_Helper(const OIDataList & input, OIDataList & output)
{
	// local vars:
	int n_to_flag = 0;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> row_dist(0, input.size() - 1);

	int n_data = CountActiveData(input);
	while(n_data > 0)
	{
		// Pick a row at random.  Be sure to copy it so that we don't modify the original data.
		OIDataRowPtr row = copy(input[ row_dist(generator) ]);

		// How many data shall we flag? Don't flag more data than remainig in n_data.
		std::uniform_int_distribution<int> flag_dist(0, row->GetMaskedNData() - 1);
		n_to_flag = fmin(n_data, flag_dist(generator));

		// Apply the mask.
		row->RandomMask(n_to_flag);
		output.push_back(row);
		n_data -= row->GetMaskedNData();
	}
}

/// Creates a data set suitable for bootstrapping by selecting Vis, V2, and T3 data in
/// spectrally dispersed chunks. Returns a copy of underlying objects.
///
/// The total number of each of Vis, V2, and T3 are conserved.
OIDataList Bootstrap_Spectral(const OIDataList & data)
{
	OIDataList output;

	OIDataList temp = FilterByDataType(data, COIDataRow::OI_VIS);
	Bootstrap_Spectral_Helper(temp, output);

	temp = FilterByDataType(data, COIDataRow::OI_VIS2);
	Bootstrap_Spectral_Helper(temp, output);

	temp = FilterByDataType(data, COIDataRow::OI_T3);
	Bootstrap_Spectral_Helper(temp, output);

	return output;
}

void Bootstrap_Spectral_Helper(const OIDataList & input, OIDataList & output)
{
	// Init a random number generator:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);

	// Generate a random distribution of the same size as the number of OI_VIS records
	std::uniform_int_distribution<int> data_dist(0, input.size() - 1);
	// Find out the total number of active data points
	int n_data = CountActiveData(input);
	while(n_data > 0)
	{
		// Include entire spectral groups by randomly including data.
		// Be sure to copy it so we don't accidently modify the original data.
		auto row = copy(input[ data_dist(generator) ]);
		output.push_back(row);
		n_data -= row->GetMaskedNData();
	}

	// Ensure that we do not include more data than the original set.
	// If we did, mask off the remainder randomly from the last appended data row.
	if(n_data < 0)
		output[output.size() - 1]->RandomMask(abs(n_data));
}

// Performs a deep copy of an OIDataList
OIDataList copy(const OIDataList & data)
{
	OIDataList output;
	for(auto row: data)
		output.push_back(copy(row));

	return output;
}

/// Performs a deep copy of an OIDataRowPtr
OIDataRowPtr copy(const OIDataRowPtr & row)
{
	// TODO: Implement copy method for OI_VIS objects:
	OIDataRowPtr output;

//	if(row->GetType() == COIDataRow::OI_VIS)
//		return OIDataRowPtr( new COIVis(row->get()));
	if(row->GetType() == COIDataRow::OI_VIS2)
		output.reset( new COIV2Row( dynamic_cast<COIV2Row*>(row.get()) ) );
	else if(row->GetType() == COIDataRow::OI_T3)
		output.reset( new COIT3Row( dynamic_cast<COIT3Row*>(row.get()) ) );

	return output;
}

/// Counts the total number of data points that are not masked out (i.e. active data)
unsigned int CountActiveData(const OIDataList & data)
{
	int n_data = 0;
	for(auto row : data)
		n_data += row->GetMaskedNData();

	return n_data;
}


/// Performs a pseudo re-calibration on the data, returning a copy of the newly calibrated data
/// The original data are left unmodified.
OIDataList Recalibrate(const OIDataList & data, OICalibratorPtr old_cal, OICalibratorPtr new_cal)
{
	// Make a deep copy of the data
	OIDataList tmp = copy(data);
	COIV2Row * v2_row;
	COIT3Row * t3_row;

	// Now recalibrate.  Use RTTI to decide which function we should call.
	for(OIDataRowPtr row: tmp)
	{
		v2_row = dynamic_cast<COIV2Row*>(row.get());
		if(v2_row != NULL)
			Recalibrate(v2_row, old_cal, new_cal);

		t3_row = dynamic_cast<COIT3Row*>(row.get());
		if(t3_row != NULL)
			Recalibrate(t3_row, old_cal, new_cal);

//		else if(row->GetType() == COIDataRow::OI_T3)
//			Recalibrate_T3(row, old_cal, new_cal);
	}

	return tmp;
}

/// Recalibrate a VIS2 row
void Recalibrate(COIV2Row * v2_row, OICalibratorPtr old_cal, OICalibratorPtr new_cal)
{
	// Get the UV point and wavelength information:
	OIUVPtr uv = v2_row->mUV[0];
	vector<double> wavelength = v2_row->GetRawWavelengths();
	int n_wave = wavelength.size();

	// Recalibrate using the ratio of the calibrators old/new:
	for(int i = 0; i < n_wave; i++)
		v2_row->v2_data[i] *= old_cal->GetV2(uv, wavelength[i]) / new_cal->GetV2(uv, wavelength[i]);
}

/// Recalibrate a T3 row
void Recalibrate(COIT3Row * t3_row, OICalibratorPtr old_cal, OICalibratorPtr new_cal)
{
	// Get the UV point and wavelength information:
	OIUVPtr uv_12 = t3_row->mUV[0];
	OIUVPtr uv_23 = t3_row->mUV[1];
	OIUVPtr uv_31 = t3_row->mUV[2];
	vector<double> wavelength = t3_row->GetRawWavelengths();
	int n_wave = wavelength.size();

	// Recalibrate using the ratio of the calibrators old/new:
	for(int i = 0; i < n_wave; i++)
		t3_row->t3_data[i] *= old_cal->GetT3(uv_12, uv_23, uv_31, wavelength[i]) / new_cal->GetT3(uv_12, uv_23, uv_31, wavelength[i]);
}

} /* namespace ccoifits */
