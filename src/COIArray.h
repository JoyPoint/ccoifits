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
	string m_array_name;
	string m_frame;
	vector<double> m_xyz;
	vector<OIStationPtr> m_stations;

public:
	COIArray(const string & array_name, const string &  frame,
			const vector<double> & xyz, const vector<OIStationPtr> & stations);
	virtual ~COIArray();

	string GetName() { return m_array_name; };
};

} /* namespace ccoifits */
#endif /* COIARRAY_H_ */
