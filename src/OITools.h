/*
 * OITools.h
 *
 *  Created on: Nov 8, 2012
 *      Author: bkloppen
 */

#ifndef OITOOLS_H_
#define OITOOLS_H_

#include <memory>
#include "COIFile.h"

using namespace std;

class COICalibrator;

namespace ccoifits
{

class COICalibrator;
typedef shared_ptr<COICalibrator> OICalibratorPtr;

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;

OIDataList Bootstrap_Random(const OIDataList & data);
OIDataList Bootstrap_Spectral(const OIDataList & data);

unsigned int CountActiveData(const OIDataList & data);

OIDataList Recalibrate(OIDataList data, OICalibratorPtr old_cal, OICalibratorPtr new_cal);
void Recalibrate_VIS2(OIDataRowPtr row, OICalibratorPtr old_cal, OICalibratorPtr new_cal);
void Recalibrate_T3(OIDataRowPtr row, OICalibratorPtr old_cal, OICalibratorPtr new_cal);


} /* namespace ccoifits */
#endif /* OITOOLS_H_ */
