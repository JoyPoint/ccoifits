/*
 * COIWavelength.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef OIWAVELENGTH_H_
#define OIWAVELENGTH_H_

#include <memory>

using namespace std;

#include "OI_TABLE.h"

namespace ccoifits
{

class COIWavelength;
typedef shared_ptr<COIWavelength> OIWavelengthPtr;

class OI_WAVELENGTH: public OI_TABLE
{
public:
	OI_WAVELENGTH(ExtHDU & table);
	virtual ~OI_WAVELENGTH();

	OIWavelengthPtr read();
};

} /* ccoifits */
#endif /* OIWAVELENGTH_H_ */
