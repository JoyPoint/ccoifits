/*
 * COIWavelength.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */


namespace ccoifits
{

#include "OI_WAVELENGTH.h"
#include "COIWavelength.h"

OI_WAVELENGTH::OI_WAVELENGTH(ExtHDU & table)
: OI_TABLE(table)
{
	// TODO Auto-generated constructor stub

}

OI_WAVELENGTH::~OI_WAVELENGTH()
{
	// TODO Auto-generated destructor stub
}

OIWavelengthPtr OI_WAVELENGTH::read()
{
	string insname = ReadKey<string>("INSNAME");
	vector<double> eff_wave = ReadColumn<double>("EFF_WAVE");
	vector<double> eff_band = ReadColumn<double>("EFF_BAND");

	return OIWavelengthPtr( new COIWavelength(insname, eff_wave, eff_band) );
}


} /* ccoifits */
