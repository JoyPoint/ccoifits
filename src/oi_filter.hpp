/*
 * OIFilter.h
 *
 *  Created on: Oct 30, 2012
 *      Author: bkloppen
 *
 *  Header file for implemented filters.
 *
 *  Filters are simply operators on OIDataLists.  OIDataLists are simply
 *  	typedef vector<OIDataRowPtr> OIDataList
 *  which, in turn are composed of shared pointers to the data rows:
 *  	typedef shared_ptr<COIDataRow> OIDataRowPtr
 *  generated from the OIFITS reading routines in CCOIFITS.
 *
 *  There are two suggested methods of implementing filters:
 *
 *  1) The first involves iterating overall OIDataRowPtr in OIDataList
 *  applying some criteria to the data. In the case of a match, the
 *  OIDataRowPtr is copied into an output vector which is later returned
 *  to the user. For an example of this, see FilterByArrayName().
 *
 *  2) If the filter needs to apply some criterian to the data, then
 *  the underlying COIDataRow object should be _copied_, the data
 *  manipulated, a new COIDataRowPtr created, and the COIDataRowPtr
 *  copied into the output vector. For an example implementation see
 *  FilterByWavelength().
 *
 */

#ifndef OIFILTER_H_
#define OIFILTER_H_

#include <vector>
#include <memory>

#include "oi_file.hpp"

using namespace std;

namespace ccoifits
{

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

OIDataList FilterByArrayName(const OIDataList & data, string array_name);
OIDataList FilterByCombinerName(const OIDataList & data, string combiner_name);
OIDataList FilterByDataType(const OIDataList & data, ccoifits::DataTypes type);
void FilterByDataType(const OIDataList & data, OIDataList & vis_rows, OIDataList & v2_rows, OIDataList & t3_rows);
OIDataList FilterByObjectCoords(const OIDataList & data, double ra, double dec, double search_radius);
OIDataList FilterByObjectName(const OIDataList & data, string object_name);
OIDataList FilterByObservationMJD(const OIDataList & data, pair<double, double> mjd_range);
//OIDataList FilterByWavelength(const OIDataList & data, pair<double,double> wavelength_range);


//OIDataList FilterByBaseline(OIDataList data, vector<OIBaseline> baselines);
//OIDataList FilterByBaselineLength(OIDataList data, vector<pair<double,double> > min_maxes);
//OIDataList FilterByObservationHA(OIDataList data);
//OIDataList FilterByStationNames(OIDataList data, vector<string> station_names);


// Assistance functions:
template<typename T>
bool InRange(T value, pair<T,T> range)
{
	if(value >= range.first && value <= range.second)
		return true;

	return false;
}

} /* namespace ccoifits */
#endif /* OIFILTER_H_ */
