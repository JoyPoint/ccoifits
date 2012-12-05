/*
 * COIData.h
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 *
 *  A base class for holding most of a row in an OIFITS table. The only thing not
 *  included are the data and data errors as they do not have the same storage
 *  format for different types of data.
 *
 *  Inheriting classes should implement the following functions:
 *
 * 		valarray<T> GetMaskedData();
 * 		valarray<T> GetMaskedDataError();
 * 		valarray<T> GetRawData();
 * 		valarray<T> GetRawDataError();
 *
 *	but as these functions are not covariant, we cannot enforce this by inserting
 *	virtual functions into the base class.  We could make this class into a template
 *	but that, in turn, would prohibit us from making lists of shared_ptr<COIDataRow>.
 *	Therefore we leave it up to the programmer to implement these functions.
 *
 */

#ifndef COIDATAROW_H_
#define COIDATAROW_H_

#include <vector>
#include <valarray>
#include <memory>
#include <complex>
#include <cassert>

#include "oi_file.hpp"

#include "COIUV.h"

using namespace std;

namespace ccoifits
{

class COI_DATA_TABLE;
typedef shared_ptr<COI_DATA_TABLE> DataTablePtr;

// Note: One must be careful with the OIDataList. It is a vector of shared_ptrs, therefore
// a copy simply increments the reference count on the underlying object.

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

class COITarget;
typedef shared_ptr<COITarget> OITargetPtr;

class COIArray;
typedef shared_ptr<COIArray> OIArrayPtr;

class COIWavelength;
typedef shared_ptr<COIWavelength> OIWavelengthPtr;

class COIDataRow
{

protected:
	DataTypes mType;

	OITargetPtr mTarget;
	OIArrayPtr mArray;
	OIWavelengthPtr mWave;

public:
	double time;
	double mjd;
	double int_time;

	vector<OIUVPtr> mUV;
	valarray<int> sta_index;
	valarray<bool> flag;

public:

	COIDataRow(OITargetPtr target, OIArrayPtr array, OIWavelengthPtr wavelength, double time, double mjd, double int_time, valarray<int> sta_index,
			valarray<bool> flag);

	COIDataRow(const COIDataRow * other);

	virtual ~COIDataRow();

	static unsigned int ComputeMasked(const valarray<bool> & flags);

	double DistanceTo(double ra, double dec);

	string GetArrayName();
	string GetCombinerName();
	string GetObjectName();

	// Functions for accessing the masked data:
	unsigned int GetMaskedNData();
	vector<double> GetMaskedWavelengths();
	vector<double> GetMaskedBandwidths();

	unsigned int GetRawNData();
	vector<double> GetRawWavelengths();
	vector<double> GetRawBandwidths();

	DataTypes GetType() { return mType; };

	void RandomMask(unsigned int n_to_flag);

	/* Templated functions below here */

	/// Applies the mask to the specified data. Both mask and data should be valarrays.
	template <typename T>
	T ApplyMask(valarray<bool> & mask, T data)
	{
		// Mask and data must have the same size.
		assert(mask.size() == data.size());

		// Determine how many elements are active in the mask and create a storage array
		unsigned int n_active = mask.size() - ComputeMasked(mask);
		T output(n_active);

		// iterate over the elements, i, of data
		for(int i = 0, j = 0; i < mask.size(); i++)
		{
			// If the data is not masked, put it into the j-th slot of the output array
			if(!mask[i])
			{
				output[j] = data[i];
				j++;
			}
		}

		return output;
	}
};

}

#endif /* COIDATA_H_ */
