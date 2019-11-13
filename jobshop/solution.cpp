#include <ctime>
#include <vector>

#include "solution.h"

bool check_time(time_t start, int limit)
{
	if (time(NULL) >= start + 60 * limit)
		return true;
	return false;
}

void job_shop(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int**& start_times, time_t start_stamp, int time_limit)
{
	start_times = new int*[jobs_c];
	for (int i = 0; i < jobs_c; ++i) start_times[i] = new int[machines_c];

	// store times of start and end of assigned jobs
	std::vector<std::vector<int>> machines_usage(machines_c);
	for (int i = 0; i < jobs_c; ++i)
		machines_usage[i].reserve(jobs_c * 2);


	while (!check_time(start_stamp, time_limit))
	{
		for (int i = 0; i < jobs_c; ++i)
		{

		}
	}
}
