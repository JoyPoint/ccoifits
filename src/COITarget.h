/*
 * COITarget.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef COITARGET_H_
#define COITARGET_H_

#include <string>

using namespace std;

namespace ccoifits
{

class COITarget
{
protected:
	int m_target_id;
	string m_target;
	double m_RA;
	double m_DEC;
	double m_equinox;
	double m_RA_err;
	double m_DEC_err;
	double m_RV;
	string m_rv_type;
	string m_rv_def;
	double m_pm_ra;
	double m_pm_dec;
	double m_pm_ra_err;
	double m_pm_dec_err;
	double m_parallax;
	double m_parallax_err;
	string m_spec_type;

public:
	COITarget(int target_id, const string & target_name,
			double RA, double DEC, double equinox, double RA_err, double DEC_err,
			double RV, const string & rv_type, const string & rv_def,
			double pm_ra, double pm_dec, double pm_ra_err, double pm_dec_err,
			double parallax, double parallax_err, const string & spec_type);

	virtual ~COITarget();

	double DistanceTo(double ra, double dec);

	int GetID() { return m_target_id; };
	string GetName() { return m_target; };
};

} /* namespace ccoifits */
#endif /* COITARGET_H_ */
