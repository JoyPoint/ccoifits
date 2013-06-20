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
#include <CCfits/CCfits>
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
		// First try to read in the column as an array
		try
		{
			mTable.column(column).readArrays(values, 0, n_rows);
		}
		catch(CCfits::Column::WrongColumnType error)
		{
			// It must not be a 2D column, so read it in as a 1D column
			valarray<T> temp_column;
			mTable.column(column).read(temp_column, 0, n_rows);

			// Now convert it to a 2D column with one entry in each row
			values.resize(temp_column.size());
			for(int i = 0; i < temp_column.size(); i++)
			{
				values[i].resize(1);
				values[i][0] = temp_column[i];
			}
		}
		return values;
	}


};

} /* namespace ccoifits */
#endif /* COI_TABLE_H_ */
