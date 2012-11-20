/*
 * COITable.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "COI_TABLE.h"

namespace ccoifits
{

COI_TABLE::COI_TABLE(ExtHDU & table)
: mTable(table)
{


}

COI_TABLE::~COI_TABLE()
{
	// TODO Auto-generated destructor stub
}

/// Reads the OIFITS OI_REVN tag and returns it.
int COI_TABLE::GetRevision()
{
	return ReadKey<int>("OI_REVN");
}

} /* namespace ccoifits */
