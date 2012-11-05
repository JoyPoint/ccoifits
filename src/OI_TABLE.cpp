/*
 * COITable.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: bkloppen
 */

#include "OI_TABLE.h"

namespace ccoifits
{

OI_TABLE::OI_TABLE(ExtHDU & table)
: mTable(table)
{


}

OI_TABLE::~OI_TABLE()
{
	// TODO Auto-generated destructor stub
}

/// Reads the OIFITS OI_REVN tag and returns it.
int OI_TABLE::GetRevision()
{
	return ReadKey<int>("OI_REVN");
}

} /* namespace ccoifits */
