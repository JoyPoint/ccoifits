/*
 * OI_VIS2.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef COI_VIS2_H_
#define COI_VIS2_H_

#include "COI_DATA_TABLE.h"

namespace ccoifits
{

class COIFile;

class COI_VIS2: public COI_DATA_TABLE
{
protected:
	COIFile * mParent;

public:
	COI_VIS2(ExtHDU & table, COIFile * parent);
	virtual ~COI_VIS2();

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* COI_VIS2_H_ */
