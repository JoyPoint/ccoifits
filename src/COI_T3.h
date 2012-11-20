/*
 * OI_T3.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef COI_T3_H_
#define COI_T3_H_

#include "COI_DATA_TABLE.h"

namespace ccoifits
{

class COIFile;

class COI_T3: public COI_DATA_TABLE
{
protected:
	COIFile * mParent;

public:
	COI_T3(ExtHDU & table, COIFile * parent);
	virtual ~COI_T3();

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* COI_T3_H_ */
