/*
 * COIFile.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIFile.h"
#include "OI_TARGET.h"
#include "COITarget.h"
#include "OI_ARRAY.h"
#include "COIArray.h"
#include "OI_WAVELENGTH.h"
#include "COIWavelength.h"

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

/// Reads the OIFITS file.  Returns an OIDataList with the data.
/// In case of an error, an empty OIDataList will be returned.
OIDataList COIFile::read()
{
	// TODO: We could probably template the OI_ARRAY and OI_WAVELENGTH reading routine
	ExtHDU * table;
	int version = 0;
	OIDataList data;

	// Read all targets, store in a vector of OITargetPtrs
	// No hashmaps are necessary as the IDs are unique already
	try
	{
		table = &mOIFITS->extension("OI_TARGET");
		OI_TARGET oi_target = OI_TARGET(*table);
		mTargets = oi_target.read();
	}
	catch(CCfits::FITS::NoSuchHDU)
	{
		return data;
	}

	// Read in all OI_ARRAY tables. Store them in a map<string, OIArrayPtr>
	version = 0;
	while(true)
	{
		try
		{
			table = &mOIFITS->extension("OI_ARRAY", version);
			OI_ARRAY oi_array = OI_ARRAY(*table);
			OIArrayPtr tmp = oi_array.read();
			mArrays[tmp->GetName()] = tmp;
		}
		catch(CCfits::FITS::NoSuchHDU)
		{
			break;
		}

		// increment the version
		version++;
	}

	// Read in all OI_WAVELENGTH tables, store them in a map<string, OIWavelengthPtr>
	version = 0;
	while(true)
	{
		try
		{
			table = &mOIFITS->extension("OI_WAVELENGTH", version);
			OI_WAVELENGTH oi_wave = OI_WAVELENGTH(*table);
			OIWavelengthPtr tmp = oi_wave.read();
			mWaves[tmp->GetName()] = tmp;
		}
		catch(CCfits::FITS::NoSuchHDU)
		{
			break;
		}
		version++;
	}

	// Now read in all OI_VIS, OI_VIS2, OI_T3 tables, associating the data with
	// the corresponding shared pointers from above. Store the results of this
	// operation in a vector<OIDataList> which we return from this function


	return data;
}

} /* namespace ccoifits */
