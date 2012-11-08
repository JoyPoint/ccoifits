/*
 * COIData.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 *
 *  A base class for holding most of a row in an OIFITS table. The only thing not
 *  included are the data and data errors.
 */

#ifndef COIDATAROW_H_
#define COIDATAROW_H_

#include <vector>
#include <valarray>
#include <memory>
#include "COIUV.h"

using namespace std;

namespace ccoifits
{

class OI_DATA_TABLE;
typedef shared_ptr<OI_DATA_TABLE> DataTablePtr;

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

class COITarget;
typedef shared_ptr<COITarget> OITargetPtr;

class COIArray;
typedef shared_ptr<COIArray> OIArrayPtr;

class COIWavelength;
typedef shared_ptr<COIWavelength> OIWavelengthPtr;

class COIDataRow
{
public:
	enum DataTypes
	{
		OI_VIS,
		OI_VIS2,
		OI_T3,
		INVALID
	};

protected:
	DataTypes mType;

	OITargetPtr mTarget;
	OIArrayPtr mArray;
	OIWavelengthPtr mWave;

public:
	int target_id;
	double time;
	double mjd;
	double int_time;

	vector<OIUVPtr> mUV;
	valarray<int> sta_index;
	valarray<bool> flag;
public:

	COIDataRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
			valarray<bool> flag);

	virtual ~COIDataRow();

	string GetArrayName();
	string GetCombinerName();
	string GetObjectName();

	double DistanceTo(double ra, double dec);

	vector<double> GetEffectiveWavelengths();
	vector<double> GetEffectiveBandwidths();
	DataTypes GetType() { return mType; };
};

}

#endif /* COIDATA_H_ */
