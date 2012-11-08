/*
 * COICalibrator.h
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#ifndef COICALIBRATOR_H_
#define COICALIBRATOR_H_

#include <complex>
#include <memory>

using namespace std;

namespace ccoifits
{

class COIUV;
typedef shared_ptr<COIUV> OIUVPtr;

class COICalibrator
{
public:
	COICalibrator();
	virtual ~COICalibrator();

//	virtual complex<double> GetVis(OIUVPtr uv, double wavelength) = 0;
	virtual double GetV2(OIUVPtr uv, double wavelength) = 0;
	virtual complex<double> GetT3(OIUVPtr uv_12, OIUVPtr uv_23, OIUVPtr uv_31, double wavelength) = 0;
};

} /* namespace ccoifits */
#endif /* COICALIBRATOR_H_ */
