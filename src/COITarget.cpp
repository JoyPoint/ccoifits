/*
 * COITarget.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COITarget.h"
#include <cmath>

using namespace std;

namespace ccoifits
{

COITarget::COITarget(	int target_id, string target, double RA, double DEC, double equinox, double RA_err, double DEC_err,
		double RV, string rv_type, string rv_def, double pm_ra, double pm_dec, double pm_ra_err, double pm_dec_err,
		double parallax, double parallax_err, string spec_type)
{
	this->target_id = target_id;
	this->target = target;
	this->RA = RA;
	this->DEC = DEC;
	this->equinox = equinox;
	this->RA_err = RA_err;
	this->DEC_err = DEC_err;
	this->RV = RV;
	this->rv_type = rv_type;
	this->rv_def = rv_def;
	this->pm_ra = pm_ra;
	this->pm_dec = pm_dec;
	this->pm_ra_err = pm_ra_err;
	this->pm_dec_err = pm_dec_err;
	this->parallax = parallax;
	this->parallax_err = parallax_err;
	this->spec_type = spec_type;
}

COITarget::~COITarget()
{
	// TODO Auto-generated destructor stub
}

/// Returns the distance between this object and the specified coordinates
/// computed in quadrature.
double COITarget::DistanceTo(double ra, double dec)
{
	double d_ra = this->RA - ra;
	double d_dec = this->DEC - dec;

	return sqrt(d_ra*d_ra + d_dec*d_dec);
}

} /* namespace ccoifits */
