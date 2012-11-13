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

namespace ccoifits
{

class COICalibrator;
class COIV2Row;
class COIT3Row;

class COICalibrator;
typedef shared_ptr<COICalibrator> OICalibratorPtr;

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;

OIDataList Bootstrap_Random(const OIDataList & data);
void Bootstrap_Random_Helper(const OIDataList & input, OIDataList & output);

OIDataList Bootstrap_Spectral(const OIDataList & data);
void Bootstrap_Spectral_Helper(const OIDataList & input, OIDataList & output);

unsigned int CountActiveData(const OIDataList & data);

OIDataList copy(const OIDataList & data);
OIDataRowPtr copy(const OIDataRowPtr & row);

OIDataList Recalibrate(const OIDataList & data, OICalibratorPtr old_cal, OICalibratorPtr new_cal);
void Recalibrate(COIV2Row * v2_row, OICalibratorPtr old_cal, OICalibratorPtr new_cal);
void Recalibrate(COIT3Row * t3_row, OICalibratorPtr old_cal, OICalibratorPtr new_cal);


} /* namespace ccoifits */
#endif /* OITOOLS_H_ */
