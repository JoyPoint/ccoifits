/*
 * COIArray.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef OIARRAY_H_
#define OIARRAY_H_

#include "OI_TABLE.h"

namespace ccoifits
{

class COIArray;
typedef shared_ptr<COIArray> OIArrayPtr;

class COIStation;
typedef shared_ptr<COIStation> OIStationPtr;

class OI_ARRAY : public OI_TABLE
{

public:
	OI_ARRAY(ExtHDU & table);
	virtual ~OI_ARRAY();

	OIArrayPtr read();

protected:
	vector<double> ReadXYZ();
	vector<OIStationPtr> ReadStations();
};

} /* namespace ccoifits */

#endif /* OIARRAY_H_ */
