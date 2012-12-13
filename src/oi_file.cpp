/*
 * COIFile.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "oi_file.hpp"
#include "COI_TARGET.h"
#include "COITarget.h"
#include "COI_ARRAY.h"
#include "COIArray.h"
#include "COI_WAVELENGTH.h"
#include "COIWavelength.h"
#include "COI_DATA_TABLE.h"
#include "COIDataRow.h"
#include "COI_VIS.h"
#include "COIVisRow.h"
#include "COI_VIS2.h"
#include "COIV2Row.h"
#include "COI_T3.h"
#include "COIT3Row.h"

#include <string>
#include <stdexcept>

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

/// Returns an OIArrayPtr with the specified ID.  If no such target exists a placeholder
/// is created and the corresponding OIArrayPtr is returned.
OIArrayPtr COIFile::GetArray(string array_name)
{
	return mArrays[array_name];
}

/// Returns an OIWavelengthPtr with the specified ID.  If no such target exists a placeholder
/// is created and the corresponding OIWavelengthPtr is returned.
OIWavelengthPtr COIFile::GetWavelength(string wavelength_name)
{
	return mWaves[wavelength_name];
}

/// Returns an OITargetPtr with the specified ID.  If no such target exists a placeholder
/// is created and the corresponding OITargetPtr is returned.
OITargetPtr COIFile::GetTarget(int target_id)
{
	return mTargets[target_id];
}

/// Opens an OIFITS file.
void COIFile::open(string filename)
{
	// Open the file
	try
	{
		open(filename, Read);
	}
	catch(CCfits::FITS::CantOpen & e)
	{
		throw runtime_error("Cannot find FITS file" + filename);
	}
}

/// Opens an OIFITS file.
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
	OIDataList data;
	int n_tables = 0;

	// Get access to the FITS extension map.
	const CCfits::ExtMap & ext = mOIFITS->extension();

	// First verify that there is an OI_TARGET table in the file, if not exit immediately.
	n_tables = ext.count("OI_TARGET");
	if(n_tables == 0)
		throw runtime_error("No OI_TARGET found in file.");

	// Read all targets, store in a map<int, OITargetPtr>
	table = &mOIFITS->extension("OI_TARGET");
	COI_TARGET oi_target = COI_TARGET(*table);
	vector<OITargetPtr> targets = oi_target.read();
	for(auto it = targets.begin(); it < targets.end(); ++it)
		mTargets[(*it)->GetID()] = (*it);

	// Read in all OI_ARRAY tables. Store them in a map<string, OIArrayPtr>
	n_tables = ext.count("OI_ARRAY");
	for(int i = 0; i < n_tables; i++)
	{
		// Read in the ith plus one entry (CCFits convention here).
		table = &mOIFITS->extension("OI_ARRAY", i+1);
		COI_ARRAY oi_array = COI_ARRAY(*table);
		OIArrayPtr tmp = oi_array.read();
		mArrays[tmp->GetName()] = tmp;
	}


	// Read in all OI_WAVELENGTH tables, store them in a map<string, OIWavelengthPtr>
	n_tables = ext.count("OI_WAVELENGTH");
	for(int i = 0; i < n_tables; i++)
	{
		// Read in the ith plus one entry (CCFits convention here).
		table = &mOIFITS->extension("OI_WAVELENGTH", i+1);
		COI_WAVELENGTH oi_wave = COI_WAVELENGTH(*table);
		OIWavelengthPtr tmp = oi_wave.read();
		mWaves[tmp->GetName()] = tmp;
	}

	// Now read in all OI_VIS, OI_VIS2, OI_T3 tables, associating the data with
	// the corresponding shared pointers from above. Store the results of this
	// operation in a vector<OIDataList> which we return from this function

	// TODO: The clunky form of iterating over tables within the OIFITS file can probably
	// be fixed using multimap::equal_range. But I'm not sure how to do this within CCFits
	// data formats.

	// First all OI_VIS records:
	n_tables = ext.count("OI_VIS");
	for(int i = 0; i < n_tables; i++)
	{
		// It is possible that the EXTVER may not be the next integer increment
		// so we'll try and catch NoSuchHDU exceptions
		try
		{
			table = &mOIFITS->extension("OI_VIS", i+1);
		}
		catch(CCfits::FITS::NoSuchHDU & e)
		{
			n_tables += 1;
			continue;
		}
		COI_VIS oi_vis = COI_VIS(*table, this);
		OIDataList tmp = oi_vis.read();
		data.insert(data.end(), tmp.begin(), tmp.end());
	}

	// Second, OI_VIS2 records:
	n_tables = ext.count("OI_VIS2");
	for(int i = 0; i < n_tables; i++)
	{
		try
		{
			table = &mOIFITS->extension("OI_VIS2", i+1);
		}
		catch(CCfits::FITS::NoSuchHDU & e)
		{
			n_tables += 1;
			continue;
		}

		COI_VIS2 oi_vis2 = COI_VIS2(*table, this);
		OIDataList tmp = oi_vis2.read();
		data.insert(data.end(), tmp.begin(), tmp.end());
	}

	// Lastly, OI_T3 records:
	n_tables = ext.count("OI_T3");
	for(int i = 0; i < n_tables; i++)
	{
		try
		{
			table = &mOIFITS->extension("OI_T3", i+1);
		}
		catch(CCfits::FITS::NoSuchHDU & e)
		{
			n_tables += 1;
			continue;
		}
		COI_T3 oi_t3 = COI_T3(*table, this);
		OIDataList tmp = oi_t3.read();
		data.insert(data.end(), tmp.begin(), tmp.end());
	}

	return data;
}

} /* namespace ccoifits */
