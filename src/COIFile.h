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

#include "COIDataRow.h"

using namespace CCfits;
using namespace std;

namespace ccoifits
{

class COITarget;
typedef shared_ptr<COITarget> OITargetPtr;

class COIArray;
typedef shared_ptr<COIArray> OIArrayPtr;

class COIWavelength;
typedef shared_ptr<COIWavelength> OIWavelengthPtr;


class COIFile
{
protected:
	auto_ptr<FITS> mOIFITS;

	vector<OITargetPtr> mTargets;
	map<string,OIArrayPtr> mArrays;	// maps mArray_map['name'] -> OIArrayPtr
	vector<OIWavelengthPtr> mWaves;

public:
	COIFile();
	virtual ~COIFile();

	void close();

	void open(string filename);
	void open(string filename, CCfits::RWmode mode);

	OIDataList read();
};

} /* namespace ccoifits */
#endif /* COIFILE_H_ */
