/*
 * COIArray.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#ifndef COI_ARRAY_H_
#define COI_ARRAY_H_

#include "COI_TABLE.h"

namespace ccoifits
{

class COIArray;
typedef shared_ptr<COIArray> OIArrayPtr;

class COIStation;
typedef shared_ptr<COIStation> OIStationPtr;

class COI_ARRAY : public COI_TABLE
{

public:
	COI_ARRAY(ExtHDU & table);
	virtual ~COI_ARRAY();

	OIArrayPtr read();

protected:
	vector<double> ReadXYZ();
	vector<OIStationPtr> ReadStations();
};

} /* namespace ccoifits */

#endif /* COI_ARRAY_H_ */
