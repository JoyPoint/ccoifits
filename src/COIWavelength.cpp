/*
 * COIWavelength.cpp
 *
 *  Created on: Nov 6, 2012
 *      Author: bkloppen
 */

#include "COIWavelength.h"

namespace ccoifits
{

COIWavelength::COIWavelength(string insname, vector<double> eff_wave, vector<double> eff_band)
{
	this->insname = insname;
	this->eff_wave = eff_wave;
	this->eff_band = eff_band;
}

COIWavelength::~COIWavelength()
{
	// TODO Auto-generated destructor stub
}

} /* namespace ccoifits */
