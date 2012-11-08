/*
 * CUniformDisk.h
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#ifndef CUNIFORMDISK_H_
#define CUNIFORMDISK_H_

#include "COICalibrator.h"

namespace ccoifits
{

class CUniformDisk: public COICalibrator
{
protected:
	double mDiameter; // stellar diameter, stored in radians.
public:
	CUniformDisk(double diameter);
	virtual ~CUniformDisk();

	complex<double> GetVis(OIUVPtr uv, double wavelength);
	double GetV2(OIUVPtr uv, double wavelength);
	complex<double> GetT3(OIUVPtr uv_12, OIUVPtr uv_23, OIUVPtr uv_31, double wavelength);
};

} /* namespace ccoifits */
#endif /* CUNIFORMDISK_H_ */
