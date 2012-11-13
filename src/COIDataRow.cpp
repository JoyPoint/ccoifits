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

COIDataRow::COIDataRow(const COIDataRow * other)
{
	mTarget = other->mTarget;
	mArray = other->mArray;
	this->time = other->time;
	this->mjd = other->mjd;
	this->int_time = other->int_time;
	this->sta_index = other->sta_index;
	this->flag = other->flag;
}

COIDataRow::~COIDataRow()
{
	// TODO Auto-generated destructor stub
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

/// Returns the total number of data points that are not masked by flags.
unsigned int COIDataRow::GetMaskedNData()
{
	return GetRawNData() - flag.sum();
}

vector<double> COIDataRow::GetMaskedWavelengths()
{
	if(mWave.get() != NULL)
		return ApplyMask(flag, mWave->eff_wave);

	vector<double> tmp;
	return tmp;
}

vector<double> COIDataRow::GetMaskedBandwidths()
{
	if(mWave.get() != NULL)
		return ApplyMask(flag, mWave->eff_band);

	vector<double> tmp;
	return tmp;
}

/// Returns the total number of data points contained in this object WITHOUT application
/// of any flags. Answer is always = N(spectral channels)
unsigned int COIDataRow::GetRawNData()
{
	return flag.size();
}

/// Returns the effective wavelengths of the data associated with this object. If there is no
/// OI_WAVELENGTH table, an empty vector is returned.
vector<double> COIDataRow::GetRawWavelengths()
{
	if(mWave.get() != NULL)
		return mWave->eff_wave;

	vector<double> tmp;
	return tmp;
}

/// Returns the effective bandwidths of the data associated with this object. If there is no
/// OI_WAVELENGTH table, an empty vector is returned.
vector<double> COIDataRow::GetRawBandwidths()
{
	if(mWave.get() != NULL)
		return mWave->eff_band;

	vector<double> tmp;
	return tmp;
}


/// Returns the name of the object as indicated by an OI_TARGET table, or an empty string.
string COIDataRow::GetObjectName()
{
	if(mTarget.get() != NULL)
		return mTarget->GetName();

	return "";
}

} /* namespace ccoifits */
