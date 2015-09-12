/*
 * COIArray.h
 *
 *  Created on: Nov 6, 2012
 *      Author: bkloppen
 */

#ifndef COIARRAY_H_
#define COIARRAY_H_

#include <memory>
#include <vector>
#include <string>

using namespace std;

namespace ccoifits
{

class COIStation;
typedef shared_ptr<COIStation> OIStationPtr;

class COIArray
{
public:
	string array_name;
	string frame;
	vector<double> xyz;
	vector<OIStationPtr> stations;

public:
	COIArray(const string & array_name, const string &  frame, const vector<double> & xyz, const vector<OIStationPtr> & stations);
	virtual ~COIArray();

	string GetName() { return array_name; };
};

} /* namespace ccoifits */
#endif /* COIARRAY_H_ */
