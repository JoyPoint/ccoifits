/*
 * ccoifits_test.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: bkloppenborg
 *
 *  Unit test framework for ccoifits
 */

#include "ccoifits_tests.h"
#include "PathFind.hpp"
#include "gtest/gtest.h"

//using namespace ccoifits;

string CCOIFITS_TEST_DATA_PATH;

int main(int argc, char **argv)
{
	// Find the path to the current executable
	string exe = FindExecutable();
	size_t folder_end = exe.find_last_of("/\\");
	CCOIFITS_TEST_DATA_PATH = exe.substr(0,folder_end+1) + "../test_data";

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
