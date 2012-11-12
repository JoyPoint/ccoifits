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

} /* namespace ccoifits */
