#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <ctime>
#include "input_output.h"
#include "solution.h"


// TODO: requirement: argument to limit number of jobs taken into account
/*
argv:
	[1] input_file
	[2] file_type
		t - Taillard's format
		b - Beasley's format (orlib)
	[3] execution time limit
	[4] job number limit
*/
int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	time_t START_TIME;

	// start counting time
	START_TIME = time(NULL);

	int** MACHINES_ORDER;   // maszyny
	int** JOB_DUR_TIMES;    // czasy
	int** start_times;		// solution
	int MACHINES_COUNT, JOBS_COUNT, MAX_JOBS = 0, TIME_LIMIT = 5;

	std::string input_file = argv[1];
	std::string file_type = argv[2];
	if (argc > 2)
	{
		MAX_JOBS = std::stoi(argv[3]);
		if (argc > 3) TIME_LIMIT = std::stoi(argv[4]);
	}

	std::cout << "filename: " << input_file << ", type: " << file_type << '\n';

	if (file_type[0] == 't' || file_type[0] == 'T')
	{
	    read_t(input_file, &MACHINES_COUNT, &JOBS_COUNT, MACHINES_ORDER, JOB_DUR_TIMES, MAX_JOBS);
		// solve
		job_shop(MACHINES_COUNT, JOBS_COUNT, MACHINES_ORDER, JOB_DUR_TIMES, start_times, START_TIME, TIME_LIMIT);
	    write_to_file("wynik_t.txt", MACHINES_COUNT, JOBS_COUNT, start_times);

		/*for (int i = 0; i < JOBS_COUNT; ++i)
		{
			for (int j = 0; j < MACHINES_COUNT; ++j)
				std::cout << JOB_DUR_TIMES[i][j] << "\t";
			std::cout << '\n';
		}*/
	}

	else if (file_type[0] == 'b' || file_type[0] == 'B')
	{
		read_b(input_file, &MACHINES_COUNT, &JOBS_COUNT, MACHINES_ORDER, JOB_DUR_TIMES, MAX_JOBS);
		// solve the problem
		job_shop(MACHINES_COUNT, JOBS_COUNT, MACHINES_ORDER, JOB_DUR_TIMES, start_times, START_TIME, TIME_LIMIT);
        write_to_file("wynik_b.txt", MACHINES_COUNT, JOBS_COUNT, start_times);
	}
	else
	{
		std::cout << "Incorrect argument format: file_type (argv[2])\n";
		return 1;
	}
	return 0;
}