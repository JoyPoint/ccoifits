/*
 * COIUV.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: bkloppen
 */

#include "COIUV.h"
#include <cmath>

using namespace std;

namespace ccoifits
{

COIUV::COIUV()
{
	 this->u = 0;
	 this->v = 0;
}

COIUV::COIUV(const COIUV & uv)
{
	this->u = uv.u;
	this->v = uv.v;
}

COIUV::COIUV(double u, double v)
{
	 this->u = u;
	 this->v = v;
}

COIUV::~COIUV()
{
	// TODO Auto-generated destructor stub
}

double COIUV::GetBaselineLength()
{
	return sqrt(u*u + v*v);
}

pair<double,double> COIUV::GetScaledPair(double wavelength)
{
	return pair<double,double>(u/wavelength, v/wavelength);
}


// Compares two pairs which are suppose to represent UV points.
// Returns 1 if the points match, 0 if they do not match, -1 if uv2 is the conjugate of uv1.
int COIUV::compare_uv(const pair<double,double> & uv1, const pair<double,double> & uv2)
{
	double threshold = 5.0e-5;

	double sqthresh = threshold * threshold;
	double pcompu = 0;
	double pcompv = 0;
	double mcompu = 0;
	double mcompv = 0;

	double denom_u = uv1.first * uv1.first + uv2.first * uv2.first;
	double denom_v = uv1.second * uv1.second + uv2.second * uv2.second;

	pcompu = 2.0*(uv1.first - uv2.first) * (uv1.first - uv2.first) / denom_u;
	pcompv = 2.0*(uv1.second - uv2.second) * (uv1.second - uv2.second) / denom_v;
	mcompu = 2.0*(uv1.first + uv2.first) * (uv1.first + uv2.first) / denom_u;
	mcompv = 2.0*(uv1.second + uv2.second) * (uv1.second + uv2.second) / denom_v;

	/* To handle zeros */
	if((uv1.first - uv2.first) == 0.0)
	{
		pcompu = 0.0;
	}
	if((uv1.second - uv2.second) == 0.0)
	{
		pcompv = 0.0;
	}
	if((uv1.first + uv2.first) == 0.0)
	{
		mcompu = 0.0;
	}
	if((uv1.second + uv2.second) == 0.0)
	{
		mcompv = 0.0;
	}

	/* If uv1 is same as uv2 then return 1 */
	if((pcompu < sqthresh) && (pcompv < sqthresh))
	{
		return 1;
	}
	/* If uv1 is same as uv2 but conjugated then return -1 */
	if((mcompu < sqthresh) && (mcompv < sqthresh))
	{
		return -1;
	}

	return 0;
}

} /* namespace ccoifits */
