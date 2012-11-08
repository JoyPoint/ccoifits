/*
 * COIDataRow.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include <limits>

#include "COIDataRow.h"
#include "COITarget.h"
#include "COIArray.h"
#include "COIWavelength.h"

using namespace std;

namespace ccoifits
{

COIDataRow::COIDataRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
		valarray<bool> flag)
{
	mTarget = target;
	mArray = array;
	mWave = wavelength;
	this->time = time;
	this->mjd = mjd;
	this->int_time = int_time;
	this->sta_index = sta_index;
	this->flag = flag;


}

COIDataRow::~COIDataRow()
{
	// TODO Auto-generated destructor stub
}

/// Returns the name of the array as indicated by the OI_ARRAY table, or an empty string.
string COIDataRow::GetArrayName()
{
	if(mArray.get() != NULL)
		return mArray->GetName();

	return "";
}

/// Returns the name of the combiner as indicated by the OI_WAVELENGTH table, or an empty string.
string COIDataRow::GetCombinerName()
{
	if(mWave.get() != NULL)
		return mWave->GetName();

	return "";
}

/// Returns the name of the object as indicated by an OI_TARGET table, or an empty string.
string COIDataRow::GetObjectName()
{
	if(mTarget.get() != NULL)
		return mTarget->GetName();

	return "";
}

/// Returns the distance between the object to which this data refers and the given coordinates.
/// If this object is not associated with a target, positive infinity is returned.
double COIDataRow::DistanceTo(double ra, double dec)
{
	if(mTarget.get() != NULL)
	{
		return mTarget->DistanceTo(ra, dec);
	}

	return std::numeric_limits<double>::max();
}

} /* namespace ccoifits */
