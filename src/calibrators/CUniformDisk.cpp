/*
 * CUniformDisk.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#include "CUniformDisk.h"

#include <cmath>
#include "COIUV.h"

namespace ccoifits
{

// Construct a uniform disk of the specified diameter (in radians);
CUniformDisk::CUniformDisk(double diameter)
{
	mDiameter = diameter;
}

CUniformDisk::~CUniformDisk()
{
	// TODO Auto-generated destructor stub
}

complex<double> CUniformDisk::GetVis(OIUVPtr uv, double wavelength)
{
	// TODO: Implement memoization to speed up computations.
	double b = uv->GetBaselineLength();
	double x = M_PI * mDiameter * b / wavelength;
	return 2 * j1(x) / x;
}

/// Returns the visibility from a uniform disk
double CUniformDisk::GetV2(OIUVPtr uv, double wavelength)
{
	complex<double> vis = GetVis(uv, wavelength);
	return norm(vis);
}

/// Returns the triple amplitude from a uniform disk
complex<double> CUniformDisk::GetT3(OIUVPtr uv_12, OIUVPtr uv_23, OIUVPtr uv_31, double wavelength)
{
	complex<double> vis_12 = GetVis(uv_12, wavelength);
	complex<double> vis_23 = GetVis(uv_12, wavelength);
	complex<double> vis_31 = GetVis(uv_12, wavelength);

	return vis_12 * vis_23 * vis_31;
}

} /* namespace ccoifits */
