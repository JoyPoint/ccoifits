/*
 * COIV2Row.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef COIVISROW_H_
#define COIVISROW_H_

#include "COIDataRow.h"

namespace ccoifits
{

class COIVisRow: public COIDataRow
{
public:
	valarray<complex<double>> vis_data;
	valarray<pair<double,double> > vis_data_err;

public:
	COIVisRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
			valarray<bool> flag, OIUVPtr uv, valarray<complex<double>> vis_data, valarray<pair<double,double> > vis_data_err);

	COIVisRow(COIVisRow * other);

	virtual ~COIVisRow();

	valarray<complex<double>> GetMaskedData();
	valarray<pair<double,double> > GetMaskedDataError();

	valarray<complex<double>> GetRawData();
	valarray<pair<double,double>> GetRawDataError();
};

} /* namespace ccoifits */
#endif /* COIVISROW_H_ */
