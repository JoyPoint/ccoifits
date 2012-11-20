/*
 * COIWavelength.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef COI_WAVELENGTH_H_
#define COI_WAVELENGTH_H_

#include <memory>

using namespace std;

#include "COI_TABLE.h"

namespace ccoifits
{

class COIWavelength;
typedef shared_ptr<COIWavelength> OIWavelengthPtr;

class COI_WAVELENGTH: public COI_TABLE
{
public:
	COI_WAVELENGTH(ExtHDU & table);
	virtual ~COI_WAVELENGTH();

	OIWavelengthPtr read();
};

} /* ccoifits */
#endif /* COI_WAVELENGTH_H_ */
