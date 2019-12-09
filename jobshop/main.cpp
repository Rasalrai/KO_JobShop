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
	[1] input file
	[2] file type
		t - Taillard's format
		b - Beasley's format (orlib)
	[3] execution time limit, in seconds [optional; default=300]
	[4] task number limit [optional, default=MAX (whole file)]
	[5] result filename [optional, default="wynik.txt"]
*/
int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	time_t START_TIME = time(nullptr);
	srand(START_TIME);
	int64_t best_time = INT64_MAX;

	std::vector< std::vector<int> > machines_order;
	std::vector< std::vector<int> > job_dur_times;
	std::vector< std::vector<int64_t> > start_times;

	int MACHINES_COUNT, JOBS_COUNT, MAX_TSK = 0, TIME_LIMIT = 300;

	std::string result_file = "wynik.txt";

	std::string input_file = argv[1];
	std::string file_type = argv[2];

	if (argc > 3)
	{
		TIME_LIMIT = std::stoi(argv[3]);

		if (argc > 4) MAX_TSK = std::stoi(argv[4]);
		if (argc > 5) result_file = argv[5];
	}

	if (file_type[0] == 't' || file_type[0] == 'T')
		read_t(input_file, MACHINES_COUNT, JOBS_COUNT, machines_order, job_dur_times);
	else if (file_type[0] == 'b' || file_type[0] == 'B')
		read_b(input_file, MACHINES_COUNT, JOBS_COUNT, machines_order, job_dur_times);
	else
	{
		std::cout << "Incorrect argument format: file_type (argv[2])\n";
		return 1;
	}
	if (!MAX_TSK) MAX_TSK = MACHINES_COUNT;
	else if (MAX_TSK > MACHINES_COUNT) MAX_TSK = MACHINES_COUNT;

	start_times = random_job_shop(MACHINES_COUNT, JOBS_COUNT, machines_order, job_dur_times, START_TIME, TIME_LIMIT, best_time, MAX_TSK);
	write_to_file(result_file, MACHINES_COUNT, JOBS_COUNT, best_time, start_times, MAX_TSK);
	return 0;
}
