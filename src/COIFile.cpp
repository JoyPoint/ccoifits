/*
 * COIFile.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIFile.h"

namespace ccoifits
{

COIFile::COIFile()
{
	// TODO Auto-generated constructor stub

}

COIFile::~COIFile()
{
	// TODO Auto-generated destructor stub
}

void COIFile::close()
{

}

void COIFile::open(string filename, RWmode mode = Read)
{
	// Open the file
	mOIFITS.reset(new FITS(filename, mode, true));
}

OIDataList COIFile::read()
{
	// Read all targets, store in a vector of OITargetPtrs
	// No hashmaps are necessary as the IDs are unique already

	// Read in all OI_ARRAY tables. Store them in a vector<OIArrayPtr>

	// Create a hashmap of OIArrayPtr->Name() -> vector.index_of(name)

	// Read in all OI_WAVELENGTH tables, store them in a vector<OIWavelengthPtr>

	// Create a hashmap of OIWavelengthPtr->Name() -> vector.index_of(name)

	// Now read in all OI_VIS, OI_VIS2, OI_T3 tables, assoicating the data with
	// the corresponding shared pointers from above. Store the results of this
	// operation in a vector<OIDataList> which we return from this function

	return OIDataList();
}


} /* namespace ccoifits */
