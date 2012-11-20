/*
 * COIWavelength.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "COI_WAVELENGTH.h"
#include "COIWavelength.h"

namespace ccoifits
{

COI_WAVELENGTH::COI_WAVELENGTH(ExtHDU & table)
: COI_TABLE(table)
{
	// TODO Auto-generated constructor stub

}

COI_WAVELENGTH::~COI_WAVELENGTH()
{
	// TODO Auto-generated destructor stub
}

OIWavelengthPtr COI_WAVELENGTH::read()
{
	string insname = ReadKey<string>("INSNAME");
	vector<double> eff_wave = ReadColumn<double>("EFF_WAVE");
	vector<double> eff_band = ReadColumn<double>("EFF_BAND");

	return OIWavelengthPtr( new COIWavelength(insname, eff_wave, eff_band) );
}


} /* ccoifits */
