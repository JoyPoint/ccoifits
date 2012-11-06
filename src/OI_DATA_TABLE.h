/*
 * OI_DATA_TABLE.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 *
 *  An abstract class for all OIFITS data tables (i.e. OI_VIS, OI_VIS2, OI_T3).
 */

#ifndef OI_DATA_TABLE_H_
#define OI_DATA_TABLE_H_

#include "OI_TABLE.h"
#include "COIDataRow.h"

namespace ccoifits
{

class OI_DATA_TABLE;
typedef shared_ptr<OI_DATA_TABLE> DataTablePtr;

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

class OI_DATA_TABLE: public OI_TABLE
{

public:
	OI_DATA_TABLE(ExtHDU & table);
	virtual ~OI_DATA_TABLE();

	string GetDateObs();
	string GetArrayName();
	string GetInstrumentName();

	virtual OIDataList read() = 0; // To be implemented by inhereting classes.
	void ReadCommon(vector<int> & target_ids, vector<double> & times, vector<double> & MJDs, vector<double> & int_times, vector< valarray<int> > & sta_indicies, vector< valarray<bool> > & flags);
};

} /* namespace ccoifits */
#endif /* OI_DATA_TABLE_H_ */
