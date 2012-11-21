/*
 * OI_VIS2.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef COI_VIS_H_
#define COI_VIS_H_

#include "COI_DATA_TABLE.h"

namespace ccoifits
{

class COIFile;

class COI_VIS: public COI_DATA_TABLE
{
protected:
	COIFile * mParent;

public:
	COI_VIS(ExtHDU & table, COIFile * parent);
	virtual ~COI_VIS();

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* COI_VIS_H_ */
