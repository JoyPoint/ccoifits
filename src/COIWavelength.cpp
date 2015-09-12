/*
 * COIWavelength.cpp
 *
 *  Created on: Nov 6, 2012
 *      Author: bkloppen
 */

#include "COIWavelength.h"

namespace ccoifits
{

COIWavelength::COIWavelength(const string & insname,
		const vector<double> & eff_wave, const vector<double> & eff_band)
	: m_insname(insname),
	  m_eff_wave(eff_wave),
	  m_eff_band(eff_band)
{
}

COIWavelength::~COIWavelength()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
