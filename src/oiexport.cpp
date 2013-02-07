/*
 * oiexport.cpp
 *
 *  Created on: Feb 7, 2013
 *      Author: bkloppen
 *
 * A program to export OIFITS files to text files
 */

#include "oiexport.h"

#include <string>
#include <iostream>

// include ccoifits headers:
#include "oi_file.hpp"
#include "oi_export.hpp"

using namespace std;
using namespace ccoifits;

int main(int argc, char **argv)
{
	// Parse the required arguments:
	string filename = "";
	string basename = "temp";
	try
	{
		filename = string(argv[1]);
		basename = string(argv[2]);
	}
	catch(...)
	{
		PrintHelp();
	}

	// Parse optional parameters
	for(int i = 0; i < argc; i++)
	{
		if (string(argv[i]) == "-h")
		{
			PrintHelp();
			return 0;
		}
	}

	// Open the file, read the data
	COIFile file;
	file.open(filename);
	OIDataList data = file.read();

	// Export the data to a text file
	ccoifits::Export_ToText(data, basename);

	return 0;
}

void PrintHelp()
{
	cout << "Running oiexport:" << endl;
	cout << " oiexport oifits output_basename" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << " -h       Print this message" << endl;
}

