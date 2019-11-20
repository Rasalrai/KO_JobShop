#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
#include <cstdint>
#include "input_output.h"
#include "solution.h"

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
	srand(time(NULL));

	// start counting time
	START_TIME = time(NULL);

	std::vector< std::vector<int> > machines_order;
	std::vector< std::vector<int> > job_dur_times;
	std::vector< std::vector<int64_t> > start_times;

	int MACHINES_COUNT, JOBS_COUNT, MAX_JOBS = 0, TIME_LIMIT = 5;

	//for (int i = 0; i < argc; ++i) std::cout << i << ' ' << argv[i] << '\t';

	std::string input_file = argv[1];
	std::string file_type = argv[2];

	if (argc > 3)
	{
		TIME_LIMIT = std::stoi(argv[3]);
		if (argc > 4) MAX_JOBS = std::stoi(argv[4]);
	}

	if (file_type[0] == 't' || file_type[0] == 'T')
	    read_t(input_file, MACHINES_COUNT, JOBS_COUNT, machines_order, job_dur_times, MAX_JOBS);
	else if (file_type[0] == 'b' || file_type[0] == 'B')
		read_b(input_file, MACHINES_COUNT, JOBS_COUNT, machines_order, job_dur_times, MAX_JOBS);
	else
	{
		std::cout << "Incorrect argument format: file_type (argv[2])\n";
		return 1;
	}
	// solve
	//std::cout << "### SOLVING ###\n\n";
	start_times = job_shop(MACHINES_COUNT, JOBS_COUNT, machines_order, job_dur_times, START_TIME, TIME_LIMIT);
	std::cout << "\n\n### OVER ###\n\n";
	write_to_file("wynik.txt", MACHINES_COUNT, JOBS_COUNT, start_times);
	return 0;
}
