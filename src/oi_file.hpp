/*
 * COIFile.h
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#ifndef COIFILE_H_
#define COIFILE_H_

#include <CCfits>
#include <memory>
#include <vector>
#include <map>

using namespace CCfits;
using namespace std;

namespace ccoifits
{

enum DataTypes
{
	OI_VIS,
	OI_VIS2,
	OI_T3,
	INVALID
};

class COITarget;
typedef shared_ptr<COITarget> OITargetPtr;

class COIArray;
typedef shared_ptr<COIArray> OIArrayPtr;

class COIWavelength;
typedef shared_ptr<COIWavelength> OIWavelengthPtr;

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

class COIFile
{
protected:
	auto_ptr<FITS> mOIFITS;

	map<int, OITargetPtr> mTargets;
	map<string, OIArrayPtr> mArrays;	// maps mArray['name'] -> OIArrayPtr
	map<string, OIWavelengthPtr> mWaves;	// maps mWaves['name'] -> OIWavelengthPtr

public:
	COIFile();
	virtual ~COIFile();

	void close();

	OIArrayPtr GetArray(string array_name);
	OIWavelengthPtr GetWavelength(string wavelength_name);
	OITargetPtr GetTarget(int target_id);

	void open(string filename);
	void open(string filename, CCfits::RWmode mode);

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* COIFILE_H_ */
