/*
 * OI_TARGET.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef COI_TARGET_H_
#define COI_TARGET_H_

#include "COI_TABLE.h"
#include <memory>

using namespace std;

namespace ccoifits
{

class COITarget;
typedef shared_ptr<COITarget> OITargetPtr;
typedef vector<OITargetPtr> OITargets;

class COI_TARGET : public COI_TABLE
{
public:
	COI_TARGET(ExtHDU & table);
	virtual ~COI_TARGET();

	OITargets read();
};

} /* namespace ccoifits */
#endif /* COI_TARGET_H_ */
