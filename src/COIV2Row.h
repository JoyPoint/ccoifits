/*
 * COIV2Row.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef COIV2ROW_H_
#define COIV2ROW_H_

#include "COIDataRow.h"

namespace ccoifits
{

class COIV2Row: public COIDataRow
{
public:
	valarray<double> v2_data;
	valarray<double> v2_data_err;

public:
	COIV2Row(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
			valarray<bool> flag, OIUVPtr uv, valarray<double> v2_data, valarray<double> v2_data_err);

	COIV2Row(COIV2Row * other);

	virtual ~COIV2Row();

	valarray<double> GetMaskedData();
	valarray<double> GetMaskedDataError();

	valarray<double> GetRawData();
	valarray<double> GetRawDataError();
};

} /* namespace ccoifits */
#endif /* COIV2ROW_H_ */
