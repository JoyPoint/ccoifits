/*
 * COIT3Row.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef COIT3ROW_H_
#define COIT3ROW_H_

#include <complex>
#include "COIDataRow.h"

using namespace std;

namespace ccoifits
{

class COIT3Row: public COIDataRow
{
public:
	COIT3Row(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
			valarray<bool> flag, valarray<complex<double>> v2_data, valarray<complex<double>> v2_data_err);

	virtual ~COIT3Row();

	valarray< complex<double> > t3_data;
	valarray< complex<double> > t3_data_err;
};

} /* namespace ccoifits */
#endif /* COIT3ROW_H_ */
