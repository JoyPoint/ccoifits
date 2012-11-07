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
		valarray<bool> flag, valarray<complex<double>> data, valarray<complex<double>> data_err)
: COIDataRow(target, array, wavelength, time, mjd, int_time, sta_index, flag)
{
	mType = DataTypes::OI_T3;
	t3_data = data;
	t3_data_err = data_err;

}

COIT3Row::~COIT3Row()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
