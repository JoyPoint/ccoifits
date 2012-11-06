/*
 * OI_VIS2.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef OI_VIS2_H_
#define OI_VIS2_H_

#include "OI_DATA_TABLE.h"

namespace ccoifits
{

class COIFile;

class OI_VIS2: public OI_DATA_TABLE
{
protected:
	COIFile * mParent;

public:
	OI_VIS2(ExtHDU & table, COIFile * parent);
	virtual ~OI_VIS2();

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* OI_VIS2_H_ */
