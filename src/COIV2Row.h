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
	COIV2Row(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
			valarray<bool> flag, valarray<double> v2_data, valarray<double> v2_data_err);

	virtual ~COIV2Row();

	valarray<double> v2_data;
	valarray<double> v2_data_err;
};

} /* namespace ccoifits */
#endif /* COIV2ROW_H_ */
