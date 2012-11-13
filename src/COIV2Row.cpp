/*
 * COIV2Row.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIV2Row.h"

namespace ccoifits
{

COIV2Row::COIV2Row(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
		valarray<bool> flag, OIUVPtr uv, valarray<double> data, valarray<double> data_err)
: COIDataRow(target, array, wavelength, time, mjd, int_time, sta_index, flag)
{
	mType = DataTypes::OI_VIS2;
	v2_data = data;
	v2_data_err = data_err;
	mUV.push_back(uv);
}

COIV2Row::COIV2Row(COIV2Row * other)
	:COIDataRow(other)
{
	mType = DataTypes::OI_VIS2;
	v2_data = other->v2_data;
	v2_data_err = other->v2_data_err;
	mUV = other->mUV;
}

COIV2Row::~COIV2Row()
{
	// TODO Auto-generated destructor stub
}

valarray<double> COIV2Row::GetMaskedData()
{
	return ApplyMask(flag, v2_data);
}

valarray<double> COIV2Row::GetMaskedDataError()
{
	return ApplyMask(flag, v2_data_err);
}

/// Returns the raw data stored in an COIV2Row without any application of a mask.
valarray<double> COIV2Row::GetRawData()
{
	return v2_data;
}

/// Returns the raw data error stored in an COIV2Row without any application of a mask.
valarray<double> COIV2Row::GetRawDataError()
{
	return v2_data_err;
}


} /* namespace ccoifits */
