/*
 * COIV2Row.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIT3Row.h"

namespace ccoifits
{

COIT3Row::COIT3Row(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength,
		double time, double mjd, double int_time,
		const valarray<int> & sta_index,
		const valarray<bool> & flag,
		OIUVPtr uv12, OIUVPtr uv23,
		const valarray<complex<double>> & t3_data,
		const valarray<pair<double,double>> & t3_data_err)
: COIDataRow(target, array, wavelength, time, mjd, int_time, sta_index, flag),
	m_t3_data(t3_data), m_t3_data_err(t3_data_err)
{
	mType = DataTypes::OI_T3;

	m_UV.push_back(uv12);
	m_UV.push_back(uv23);

	// Construct the uv31 UV point:
	OIUVPtr uv31 = OIUVPtr( new COIUV );
	uv31->m_u = uv12->m_u + uv23->m_u;
	uv31->m_v = uv12->m_v + uv23->m_v;
	m_UV.push_back(uv31);
}

COIT3Row::COIT3Row(COIT3Row * other)
: COIDataRow(other)
{
	mType = DataTypes::OI_T3;
	m_t3_data = other->m_t3_data;
	m_t3_data_err = other->m_t3_data_err;
	m_UV = other->m_UV;
}

COIT3Row::~COIT3Row()
{
	// TODO Auto-generated destructor stub
}

valarray<complex<double>> COIT3Row::GetMaskedData()
{
	return ApplyMask(m_flag, m_t3_data);
}

valarray<pair<double,double>> COIT3Row::GetMaskedDataError()
{
	return ApplyMask(m_flag, m_t3_data_err);
}

/// Returns the raw data stored in an OIT3Row without any application of a mask.
valarray<complex<double>> COIT3Row::GetRawData()
{
	return m_t3_data;
}

/// Returns the raw data error stored in an OIT3Row without any application of a mask.
valarray<pair<double,double>> COIT3Row::GetRawDataError()
{
	return m_t3_data_err;
}

} /* namespace ccoifits */
