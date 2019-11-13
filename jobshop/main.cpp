#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

#include "input_output.h"
// TODO: requirement: argument to limit number of jobs taken into account
/*
argv:
	[1] inFileName
	[2] fileType
		t - Taillard's format
		b - Beasley's format (orlib)
*/
int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);
	std::string inFileName = argv[1];
	std::string fileType = argv[2];

	std::cout << "filename: " << inFileName << ", type: " << fileType << '\n';

	if (fileType[0] == 't' || fileType[0] == 'T')
	{
	    read_t(inFileName);
	    write_to_file("wynik_t.txt");
	}

	else if (fileType[0] == 'b' || fileType[0] == 'B')
	{
		read_b(inFileName);
        write_to_file("wynik_b.txt");
	}
	else
	    std::cout << "Incorrect argument format: fileType (argv[2])\n";

	return 0;
}