/*
 * OITools.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#include "OITools.h"
#include "OIFilter.h"
#include "COIDataRow.h"
#include "COIWavelength.h"
#include "COIV2Row.h"
#include "COIT3Row.h"
#include "COICalibrator.h"

namespace ccoifits
{

/// Performs a pseudo re-calibration on the data, returning a copy of the newly calibrated data
OIDataList Recalibrate(OIDataList data, OICalibratorPtr old_cal, OICalibratorPtr new_cal)
{
	// Notice we are passing by value, so we have a COPY of the original vector.
	// We can safely modify its content without issues.
	for(OIDataRowPtr row: data)
	{
		if(row->GetType() == COIDataRow::OI_VIS2)
			Recalibrate_VIS2(row, old_cal, new_cal);
		else if(row->GetType() == COIDataRow::OI_T3)
			Recalibrate_T3(row, old_cal, new_cal);
	}

	return data;
}

/// Recalibrate a VIS2 row
void Recalibrate_VIS2(OIDataRowPtr row, OICalibratorPtr old_cal, OICalibratorPtr new_cal)
{
	// Verify we truly have an OI_VIS2 record, if not, do nothing.
	if(row->GetType() != COIDataRow::OI_VIS2)
		return;

	// We have an OI_VIS2 object, dynamic cast it as so:
	COIV2Row * v2_row = dynamic_cast<COIV2Row*>(row.get());

	// Get the UV point and wavelength information:
	OIUVPtr uv = v2_row->mUV[0];
	vector<double> wavelength = v2_row->GetEffectiveWavelengths();
	int n_wave =wavelength.size();

	// Recalibrate using the ratio of the calibrators old/new:
	for(int i = 0; i < n_wave; i++)
		v2_row->v2_data[i] *= old_cal->GetV2(uv, wavelength[i]) / new_cal->GetV2(uv, wavelength[i]);
}

/// Recalibrate a T3 row
void Recalibrate_T3(OIDataRowPtr row, OICalibratorPtr old_cal, OICalibratorPtr new_cal)
{
	// Verify we truly have an OI_VIS2 record, if not, do nothing.
	if(row->GetType() != COIDataRow::OI_T3)
		return;

	// We have an OI_VIS2 object, dynamic cast it as so:
	COIT3Row * t3_row = dynamic_cast<COIT3Row*>(row.get());

	// Get the UV point and wavelength information:
	OIUVPtr uv_12 = t3_row->mUV[0];
	OIUVPtr uv_23 = t3_row->mUV[1];
	OIUVPtr uv_31 = t3_row->mUV[2];
	vector<double> wavelength = t3_row->GetEffectiveWavelengths();
	int n_wave =wavelength.size();

	// Recalibrate using the ratio of the calibrators old/new:
	for(int i = 0; i < n_wave; i++)
		t3_row->t3_data[i] *= old_cal->GetT3(uv_12, uv_23, uv_31, wavelength[i]) / new_cal->GetT3(uv_12, uv_23, uv_31, wavelength[i]);
}

} /* namespace ccoifits */
