/*
 * OI_TARGET.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef OI_TARGET_H_
#define OI_TARGET_H_

#include "OI_TABLE.h"

class COITarget;
typename shared_ptr<COITarget> OITargetPtr;
typename vector<COITargetPtr> OITargets;

namespace ccoifits
{

class OI_TARGET : public OI_TABLE
{
public:
	OI_TARGET(ExtHDU & table);
	virtual ~OI_TARGET();

	OITargets read();
};

} /* namespace ccoifits */
#endif /* OI_TARGET_H_ */
