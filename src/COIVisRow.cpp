/*
 * COIV2Row.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: bkloppen
 */

#include "COIVisRow.h"

namespace ccoifits
{

COIVisRow::COIVisRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength,
		double time, double mjd, double int_time,
		const valarray<int> & sta_index,
		const valarray<bool> & flag, OIUVPtr uv,
		const valarray<complex<double>> & vis_data,
		const valarray<pair<double,double> > & vis_data_err)
	: COIDataRow(target, array, wavelength, time, mjd, int_time, sta_index, flag),
	  m_vis_data(vis_data),
	  m_vis_data_err(vis_data_err)
{
	mType = DataTypes::OI_VIS;
	m_UV.push_back(uv);
}

COIVisRow::COIVisRow(COIVisRow * other)
	:COIDataRow(other)
{
	mType = DataTypes::OI_VIS;
	m_vis_data = other->m_vis_data;
	m_vis_data_err = other->m_vis_data_err;
	m_UV = other->m_UV;
}

COIVisRow::~COIVisRow()
{
	// TODO Auto-generated destructor stub
}

valarray<complex<double>> COIVisRow::GetMaskedData()
{
	return ApplyMask(m_flag, m_vis_data);
}

valarray<pair<double,double> > COIVisRow::GetMaskedDataError()
{
	return ApplyMask(m_flag, m_vis_data_err);
}

/// Returns the raw data stored in an COIV2Row without any application of a mask.
valarray<complex<double>> COIVisRow::GetRawData()
{
	return m_vis_data;
}

/// Returns the raw data error stored in an COIV2Row without any application of a mask.
valarray<pair<double,double> > COIVisRow::GetRawDataError()
{
	return m_vis_data_err;
}


} /* namespace ccoifits */
