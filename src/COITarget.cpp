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

COITarget::COITarget(int target_id, const string & target_name,
		double RA, double DEC, double equinox, double RA_err, double DEC_err,
		double RV, const string & rv_type, const string & rv_def,
		double pm_ra, double pm_dec, double pm_ra_err, double pm_dec_err,
		double parallax, double parallax_err, const string & spec_type)
	: m_target_id(target_id), m_target(target_name),
	  m_RA(RA), m_DEC(DEC), m_equinox(equinox), m_RA_err(RA_err), m_DEC_err(DEC_err),
	  m_RV(RV), m_rv_type(rv_type), m_rv_def(rv_def),
	  m_pm_ra(pm_ra), m_pm_dec(pm_dec), m_pm_ra_err(pm_ra_err), m_pm_dec_err(pm_dec_err),
	  m_parallax(parallax), m_parallax_err(parallax_err), m_spec_type(spec_type)
{
}

COITarget::~COITarget()
{
	// TODO Auto-generated destructor stub
}

/// Returns the distance between this object and the specified coordinates
/// computed in quadrature.
double COITarget::DistanceTo(double ra, double dec)
{
	double d_ra = this->m_RA - ra;
	double d_dec = this->m_DEC - dec;

	return sqrt(d_ra*d_ra + d_dec*d_dec);
}

} /* namespace ccoifits */
