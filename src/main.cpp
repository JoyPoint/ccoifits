/*
 * main.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: bkloppen
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <iostream>
#include "main.h"
#include "COIFile.h"
#include "OIFilter.h"
#include "OITools.h"
#include "CUniformDisk.h"

using namespace std;
using namespace ccoifits;

int main(int argc, char *argv[])
{
	COIFile tmp;
	try
	{
		tmp.open("/homes/bkloppen/workspace/ccoifits/bin/test.oifits");
	}
	catch(CCfits::FITS::CantOpen)
	{
		cout << "Couldn't find FITS file" << endl;
	}

	OIDataList data = tmp.read();
	cout << "Found " << data.size() << " data points." << endl;

	OIDataList V2 = FilterByDataType(data, COIDataRow::OI_VIS2);
	cout << "Found " << V2.size() << " V2s." << endl;

	OIDataList T3 = FilterByDataType(data, COIDataRow::OI_T3);
	cout << "Found " << T3.size() << " T3s." << endl;

	cout << "Distance to eps Aur: " << data[0]->DistanceTo(075.49221855, 43.82330720) << endl;

	OICalibratorPtr old_cal = OICalibratorPtr( new CUniformDisk(0.4 * MAS_TO_RAD) );
	OICalibratorPtr new_cal = OICalibratorPtr( new CUniformDisk(0.5 * MAS_TO_RAD) );
	OIDataList recal = Recalibrate(data, old_cal, new_cal);
}

#endif // MAIN_CPP_
