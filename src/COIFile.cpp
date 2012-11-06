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
#include "OI_DATA_TABLE.h"
#include "COIDataRow.h"
#include "OI_VIS2.h"
#include "COIV2Row.h"

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
	return mTargets[target_id - 1];
}

/// Opens an OIFITS file.
void COIFile::open(string filename)
{
	// Open the file
	open(filename, Read);
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
		throw "No OI_TARGET found in file.";

	// Read all targets, store in a map<int, OITargetPtr>
	table = &mOIFITS->extension("OI_TARGET");
	OI_TARGET oi_target = OI_TARGET(*table);
	vector<OITargetPtr> targets = oi_target.read();
	for(auto it = targets.begin(); it < targets.end(); ++it)
		mTargets[(*it)->GetID()] = (*it);

	// Read in all OI_ARRAY tables. Store them in a map<string, OIArrayPtr>
	n_tables = ext.count("OI_ARRAY");
	for(int i = 0; i < n_tables; i++)
	{
		// Read in the ith plus one entry (CCFits convention here).
		table = &mOIFITS->extension("OI_ARRAY", i+1);
		OI_ARRAY oi_array = OI_ARRAY(*table);
		OIArrayPtr tmp = oi_array.read();
		mArrays[tmp->GetName()] = tmp;
	}


	// Read in all OI_WAVELENGTH tables, store them in a map<string, OIWavelengthPtr>
	n_tables = ext.count("OI_WAVELENGTH");
	for(int i = 0; i < n_tables; i++)
	{
		// Read in the ith plus one entry (CCFits convention here).
		table = &mOIFITS->extension("OI_WAVELENGTH", i+1);
		OI_WAVELENGTH oi_wave = OI_WAVELENGTH(*table);
		OIWavelengthPtr tmp = oi_wave.read();
		mWaves[tmp->GetName()] = tmp;

	}

	// Now read in all OI_VIS, OI_VIS2, OI_T3 tables, associating the data with
	// the corresponding shared pointers from above. Store the results of this
	// operation in a vector<OIDataList> which we return from this function

	// First all OI_VIS records:

	// Second, OI_VIS2 records:
	n_tables = ext.count("OI_VIS2");
//	cout << "Found " << n_tables << " OI_VIS2 tables." << endl;
	for(int i = 0; i < n_tables; i++)
	{
		table = &mOIFITS->extension("OI_VIS2", i+1);
		OI_VIS2 oi_vis2 = OI_VIS2(*table, this);
		OIDataList tmp = oi_vis2.read();
		data.insert(data.end(), tmp.begin(), tmp.end());
	}

	return data;
}

} /* namespace ccoifits */
