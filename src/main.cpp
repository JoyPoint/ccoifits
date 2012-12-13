/*
 * main.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: bkloppen
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <iostream>
#include <cassert>

#include "main.h"
#include "PathFind.hpp"
#include "oi_file.hpp"
#include "oi_filter.hpp"

//#include "oi_tools.hpp"
//#include "CUniformDisk.h"
//
//#include "COIV2Row.h"

using namespace std;
using namespace ccoifits;

int main(int argc, char *argv[])
{
	// Find the path to the current executable
	string exe = FindExecutable();
	// Find the directory (the name of this program is "ccoifits_tests", so just strip off 14 characters)
	string path = exe.substr(0, exe.size() - 18);

	string file = path + "../samples/UDD-2_5mas_nonoise.oifits";

	COIFile tmp;
	try
	{
		tmp.open(file);
	}
	catch(CCfits::FITS::CantOpen)
	{
		cout << "Couldn't find FITS file: " << file << endl;
	}

	OIDataList data = tmp.read();
	OIDataList vis;
	OIDataList v2;
	OIDataList t3;
	FilterByDataType(data, vis, v2, t3);

	// In this file we know the following
	assert(vis.size() == 75);
	assert(v2.size() == 75);
	assert(t3.size() == 100);

	cout << "All ok." << endl;
//
//	cout << "Distance to eps Aur: " << data[0]->DistanceTo(075.49221855, 43.82330720) << endl;
//
//	COIV2Row * a = reinterpret_cast<COIV2Row *>(data[0].get());
//	cout << "Original: " << a->v2_data[0];
//
//	// Try doing a recalibration:
//	OICalibratorPtr old_cal = OICalibratorPtr( new CUniformDisk(0.4 * MAS_TO_RAD) );
//	OICalibratorPtr new_cal = OICalibratorPtr( new CUniformDisk(0.5 * MAS_TO_RAD) );
//	OIDataList recal = Recalibrate(data, old_cal, new_cal);
//	// Check it
//	a = reinterpret_cast<COIV2Row *>(data[0].get());
//	COIV2Row * b = reinterpret_cast<COIV2Row *>(recal[0].get());
//	cout << ", Original post-recal: " << a->v2_data[0] << ", Recal: " << b->v2_data[0] << endl;
//
//	// Spectral bootstrap test
//	OIDataList boot_spec = Bootstrap_Spectral(data);
//	OIDataList bs_V2 = FilterByDataType(data, ccoifits::OI_VIS2);
//	OIDataList bs_T3 = FilterByDataType(data, ccoifits::OI_T3);
//	cout << "Trying spectral bootstrap. Pre N(rows): " << data.size() << " post: " << boot_spec.size() << endl;
//	cout << "N(V2) before: " << CountActiveData(V2) << " and after: " << CountActiveData(bs_V2) << endl;
//	cout << "N(T3) before: " << CountActiveData(T3) << " and after: " << CountActiveData(bs_T3) << endl;
//
//	// Random bootstrap test
//	OIDataList boot_rand = Bootstrap_Random(data);
//	OIDataList br_V2 = FilterByDataType(data, ccoifits::OI_VIS2);
//	OIDataList br_T3 = FilterByDataType(data, ccoifits::OI_T3);
//	cout << "Trying random bootstrap. Pre N(rows): " << data.size() << " post: " << boot_rand.size() << endl;
//	cout << "N(V2) before: " << CountActiveData(V2) << " and after: " << CountActiveData(br_V2) << endl;
//	cout << "N(T3) before: " << CountActiveData(T3) << " and after: " << CountActiveData(br_T3) << endl;
//
//	return 0;
}

#endif // MAIN_CPP_
