/*
 * COIDataRow.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIDataRow.h"
#include "COITarget.h"
#include "COIArray.h"
#include "COIWavelength.h"

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


string COIDataRow::GetArrayName()
{
	if(mArray.get() != NULL)
		return mArray->GetName();

	return "";
}

string COIDataRow::GetCombinerName()
{
	if(mWave.get() != NULL)
		return mWave->GetName();

	return "";
}

string COIDataRow::GetObjectName()
{
	if(mTarget.get() != NULL)
		return mTarget->GetName();

	return "";
}

double COIDataRow::DistanceTo(double ra, double dec)
{

}

} /* namespace ccoifits */
