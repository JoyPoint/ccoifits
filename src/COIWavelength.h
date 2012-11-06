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
	string insname;
	vector<double> eff_wave;
	vector<double> eff_band;

public:
	COIWavelength(string insname, vector<double> eff_wave, vector<double> eff_band);
	virtual ~COIWavelength();

	string GetName() { return insname; };
};

} /* namespace ccoifits */
#endif /* COIWAVELENGTH_H_ */
