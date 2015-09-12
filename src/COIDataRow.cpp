/*
 * COIDataRow.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include <limits>
#include <random>
// TODO: Swap <ctime> for <chrono> when clang supports c++11
#include <ctime>

#include "COIDataRow.h"
#include "COITarget.h"
#include "COIArray.h"
#include "COIWavelength.h"

using namespace std;

namespace ccoifits
{

COIDataRow::COIDataRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength,
		double time, double mjd, double int_time,
		const valarray<int> & sta_index,
		const valarray<bool> & flag)
	: mTarget(target), mArray(array), mWave(wavelength), m_time(time), m_mjd(mjd),
	m_int_time(int_time), m_sta_index(sta_index), m_flag(flag)
{

}

COIDataRow::COIDataRow(const COIDataRow * other)
{
	mTarget = other->mTarget;
	mArray = other->mArray;
	mWave = other->mWave;
	this->m_time = other->m_time;
	this->m_mjd = other->m_mjd;
	this->m_int_time = other->m_int_time;
	this->m_sta_index = other->m_sta_index;
	this->m_flag = other->m_flag;
}

COIDataRow::~COIDataRow()
{
	// TODO Auto-generated destructor stub
}

unsigned int COIDataRow::ComputeMasked(const valarray<bool> & flags)
{
	unsigned int flag_sum = 0;
	for(auto flag: flags)
	{
		if(flag) flag_sum += 1;
	}

	return flag_sum;
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
	return GetRawNData() - ComputeMasked(m_flag);
}

vector<double> COIDataRow::GetMaskedWavelengths()
{
	if(mWave.get() != NULL)
		return ApplyMask(m_flag, mWave->m_eff_wave);

	vector<double> tmp;
	return tmp;
}

vector<double> COIDataRow::GetMaskedBandwidths()
{
	if(mWave.get() != NULL)
		return ApplyMask(m_flag, mWave->m_eff_band);

	vector<double> tmp;
	return tmp;
}

/// Returns the total number of data points contained in this object WITHOUT application
/// of any flags. Answer is always = N(spectral channels)
unsigned int COIDataRow::GetRawNData()
{
	return m_flag.size();
}

/// Returns the effective wavelengths of the data associated with this object. If there is no
/// OI_WAVELENGTH table, an empty vector is returned.
vector<double> COIDataRow::GetRawWavelengths()
{
	if(mWave.get() != NULL)
		return mWave->m_eff_wave;

	vector<double> tmp;
	return tmp;
}

/// Returns the effective bandwidths of the data associated with this object. If there is no
/// OI_WAVELENGTH table, an empty vector is returned.
vector<double> COIDataRow::GetRawBandwidths()
{
	if(mWave.get() != NULL)
		return mWave->m_eff_band;

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

/// Sets n_to_flag flags at random.
void COIDataRow::RandomMask(unsigned int n_to_flag)
{
	// The number of flags to set must always be less than the number of unflagged parameters.
	assert(n_to_flag < GetMaskedNData());

	unsigned seed = std::time(0);
	// TODO: Enable when clang fully supports C++11
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> flag_dist(0, m_flag.size() - 1);
	unsigned int entry = 0;

	// flag n_to_flag data points at random.
	while(n_to_flag > 0)
	{
		// Pick a flag at random
		entry = flag_dist(generator);

		if(!m_flag[entry])
		{
			m_flag[entry] = true;
			n_to_flag--;
		}
	}
}

} /* namespace ccoifits */
