/*
 * COIUV.h
 *
 *  Created on: Nov 7, 2012
 *      Author: bkloppen
 */

#ifndef COIUV_H_
#define COIUV_H_

#include <memory>
#include <cmath>

using namespace std;

namespace ccoifits
{

class COIUV;
typedef shared_ptr<COIUV> OIUVPtr;

class COIUV
{
public:
	double m_u;
	double m_v;

public:
	COIUV();
	COIUV(const COIUV & uv);
	COIUV(double u, double v);
	virtual ~COIUV();

	double GetBaselineLength();
	pair<double,double> GetScaledPair(double wavelength);

	static int compare_uv(const pair<double,double> & uv1, const pair<double,double> & uv2);

	COIUV operator +(const COIUV & rhs)
	{
		return COIUV(this->m_u + rhs.m_u, this->m_v + rhs.m_v);
	}

	COIUV operator -(const COIUV & rhs)
	{
		return COIUV(this->m_u - rhs.m_u, this->m_v - rhs.m_v);
	}

//	bool operator ==(const COIUV & rhs)
//	{
//		double du = this->m_u - rhs.u;
//		double dv = this->m_v - rhs.v;
//
//		if(sqrt(du*du + dv*dv) < UV_THRESHOLD)
//			return true;
//
//		return false;
//	}

	template <typename T>
	bool operator *(T val)
	{
		this->m_u * val;
		this->m_v * val;

		return true;
	}
};

} /* namespace ccoifits */
#endif /* COIUV_H_ */
