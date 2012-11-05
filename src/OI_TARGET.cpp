/*
 * OI_TARGET.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "OI_TARGET.h"
#include "COITarget.h"

namespace ccoifits
{

OI_TARGET::OI_TARGET(ExtHDU & table)
: OI_TABLE(table)
{
	// TODO Auto-generated constructor stub

}

OI_TARGET::~OI_TARGET()
{
	// TODO Auto-generated destructor stub
}

/// Reads in the target table inside of an OIFITS file.
OITargets OI_TARGET::read()
{
	// First read in all of the columns in the target table.
	// All columns are mandatory and should be free of exception errors.
	vector<int> target_ids = ReadColumn<int>("TARGET_ID");
	vector<string> targets = ReadColumn<string>("TARGET");
	vector<double> RAs = ReadColumn<double>("RAEP0");
	vector<double> DECs = ReadColumn<double>("DECEP0");
	vector<double> equinoxes = ReadColumn<double>("EQUINOX");
	vector<double> RA_errs = ReadColumn<double>("RA_ERR");
	vector<double> DEC_errs = ReadColumn<double>("DEC_ERR");
	vector<double> RVs = ReadColumn<double>("SYSVEL");
	vector<string> rv_type = ReadColumn<string>("VELTYP");
	vector<string> rv_def = ReadColumn<string>("VELDEF");
	vector<double> pm_ra = ReadColumn<double>("PMRA");
	vector<double> pm_dec = ReadColumn<double>("PMDEC");
	vector<double> pm_ra_err = ReadColumn<double>("PMRA_ERR");
	vector<double> pm_dec_err = ReadColumn<double>("PMDEC_ERR");
	vector<double> parallax = ReadColumn<double>("PARALLAX");
	vector<double> parallax_err = ReadColumn<double>("PARA_ERR");
	vector<string> spec_type = ReadColumn<string>("SPECTYP");

	// Construct
	OITargets output;
	int n_rows = mTable.rows();

	for(int i = 0; i < n_rows; i++)
	{
		OITargetPtr tmp(new COITarget(target_ids[i], targets[i], RAs[i], DECs[i], equinoxes[i], RA_errs[i], DEC_errs[i],
				RVs[i], rv_type[i], rv_def[i],
				pm_ra[i], pm_dec[i], pm_ra_err[i], pm_dec_err[i],
				parallax[i], parallax_err[i], spec_type[i]));

		output.push_back(tmp);
	}


}

} /* namespace ccoifits */
