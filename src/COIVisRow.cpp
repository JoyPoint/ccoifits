/*
 * COIV2Row.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIVisRow.h"

namespace ccoifits
{

COIVisRow::COIVisRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
		valarray<bool> flag, OIUVPtr uv, valarray<complex<double>> data, valarray<pair<double,double> > data_err)
: COIDataRow(target, array, wavelength, time, mjd, int_time, sta_index, flag)
{
	mType = DataTypes::OI_VIS;
	vis_data = data;
	vis_data_err = data_err;
	mUV.push_back(uv);
}

COIVisRow::COIVisRow(COIVisRow * other)
	:COIDataRow(other)
{
	mType = DataTypes::OI_VIS;
	vis_data = other->vis_data;
	vis_data_err = other->vis_data_err;
	mUV = other->mUV;
}

COIVisRow::~COIVisRow()
{
	// TODO Auto-generated destructor stub
}

valarray<complex<double>> COIVisRow::GetMaskedData()
{
	return ApplyMask(flag, vis_data);
}

valarray<pair<double,double> > COIVisRow::GetMaskedDataError()
{
	return ApplyMask(flag, vis_data_err);
}

/// Returns the raw data stored in an COIV2Row without any application of a mask.
valarray<complex<double>> COIVisRow::GetRawData()
{
	return vis_data;
}

/// Returns the raw data error stored in an COIV2Row without any application of a mask.
valarray<pair<double,double> > COIVisRow::GetRawDataError()
{
	return vis_data_err;
}


} /* namespace ccoifits */
