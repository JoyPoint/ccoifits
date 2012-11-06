/*
 * OI_TARGET.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef OI_TARGET_H_
#define OI_TARGET_H_

#include "OI_TABLE.h"
#include <memory>

using namespace std;

namespace ccoifits
{

class COITarget;
typedef shared_ptr<COITarget> OITargetPtr;
typedef vector<OITargetPtr> OITargets;

class OI_TARGET : public OI_TABLE
{
public:
	OI_TARGET(ExtHDU & table);
	virtual ~OI_TARGET();

	OITargets read();
};

} /* namespace ccoifits */
#endif /* OI_TARGET_H_ */
