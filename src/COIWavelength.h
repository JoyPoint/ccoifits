/*
 * COIWavelength.h
 *
 *  Created on: Nov 6, 2012
 *      Author: bkloppen
 */

#ifndef COIWAVELENGTH_H_
#define COIWAVELENGTH_H_

#include <string>
#include <vector>

using namespace std;

namespace ccoifits
{

class COIWavelength
{
public:
	string m_insname;
	vector<double> m_eff_wave;
	vector<double> m_eff_band;

public:
	COIWavelength(const string & insname,
			const vector<double> & eff_wave, const vector<double> & eff_band);
	virtual ~COIWavelength();

	string GetName() { return m_insname; };
};

} /* namespace ccoifits */
#endif /* COIWAVELENGTH_H_ */
