/*
 * COITable.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 *
 *  A base class for all OIFITS tables.
 *
 *  NOTE: As CCFITS caches table values in memory, we need not do any caching
 *  here or in derived classes unless the work is computationally expensive.
 */

#ifndef COI_TABLE_H_
#define COI_TABLE_H_

#include <array>
#include <valarray>
#include <memory>
#include <CCfits>
#include <utility>

using namespace std;
using namespace CCfits;

namespace ccoifits
{

class COI_TABLE
{
protected:
	ExtHDU & mTable;

public:
	COI_TABLE(ExtHDU & table);
	virtual ~COI_TABLE();

	int GetRevision();

	template <typename T>
	T ReadKey(string key)
	{
		T value;
		mTable.readKey(key, value);
		return value;
	}

	template <typename T>
	vector<T> ReadColumn(string column)
	{
		vector<T> values;
		int n_rows = mTable.rows();
		mTable.column(column).read( values, 1, n_rows );
	    return values;
	}

	template <typename T>
	valarray<T> ReadCells(string column, int row)
	{
		valarray<T> values;
		// Read the values.  Note CCOIFITS uses indexing from one, but we anticipate
		// C++ developers will use zero indexing.  Increment the row by one.
		mTable.column(column).read(values, row);
		return values;
	}

	template <typename T>
	vector< valarray<T> > ReadArray(string column)
	{
		vector< valarray<T> > values;
		int n_rows = mTable.rows();
		mTable.column(column).readArrays(values, 1, n_rows);
		return values;
	}


};

} /* namespace ccoifits */
#endif /* COI_TABLE_H_ */
