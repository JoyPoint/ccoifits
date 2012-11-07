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

COIV2Row::~COIV2Row()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
