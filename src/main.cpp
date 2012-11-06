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
}

#endif // MAIN_CPP_
