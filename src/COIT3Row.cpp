/*
 * COIV2Row.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIT3Row.h"

namespace ccoifits
{

COIT3Row::COIT3Row(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
		valarray<bool> flag, OIUVPtr uv12, OIUVPtr uv23, valarray<complex<double>> data, valarray<complex<double>> data_err)
: COIDataRow(target, array, wavelength, time, mjd, int_time, sta_index, flag)
{
	mType = DataTypes::OI_T3;
	t3_data = data;
	t3_data_err = data_err;

	mUV.push_back(uv12);
	mUV.push_back(uv23);

	// Construct the uv31 UV point:
	OIUVPtr uv31 = OIUVPtr( new COIUV );
	uv31->u = -(uv12->u + uv23->u);
	uv31->v = -(uv12->v + uv23->v);
	mUV.push_back(uv31);
}

COIT3Row::COIT3Row(COIT3Row * other)
: COIDataRow(other)
{
	mType = DataTypes::OI_T3;
	t3_data = other->t3_data;
	t3_data_err = other->t3_data_err;
	mUV = other->mUV;
}

COIT3Row::~COIT3Row()
{
	// TODO Auto-generated destructor stub
}

valarray<complex<double>> COIT3Row::GetMaskedData()
{
	return ApplyMask(flag, t3_data);
}

valarray<complex<double>> COIT3Row::GetMaskedDataError()
{
	return ApplyMask(flag, t3_data_err);
}

/// Returns the raw data stored in an OIT3Row without any application of a mask.
valarray<complex<double>> COIT3Row::GetRawData()
{
	return t3_data;
}

/// Returns the raw data error stored in an OIT3Row without any application of a mask.
valarray<complex<double>> COIT3Row::GetRawDataError()
{
	return t3_data_err;
}

} /* namespace ccoifits */
