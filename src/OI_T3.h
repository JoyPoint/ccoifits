/*
 * OI_T3.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef OI_T3_H_
#define OI_T3_H_

#include "OI_DATA_TABLE.h"

namespace ccoifits
{

class COIFile;

class OI_T3: public OI_DATA_TABLE
{
protected:
	COIFile * mParent;

public:
	OI_T3(ExtHDU & table, COIFile * parent);
	virtual ~OI_T3();

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* OI_T3_H_ */
