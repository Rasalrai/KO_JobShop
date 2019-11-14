#include <ctime>
#include <vector>

#include "solution.h"
#define MAXINT 2147483647

bool time_passed(time_t start, int limit)
/* true if _limit_ minutes passed since beginning of execution of the program */
{
	if (time(NULL) >= start + 60 * limit)
		return true;
	return false;
}

void job_shop(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int**& start_times, time_t start_stamp, int time_limit)
{
	// storing iterations' data
	std::vector<std::vector<int>> machines_usage(machines_c);
	for (int i = 0; i < machines_c; ++i)
	{
		machines_usage[i].reserve(jobs_c * 2);
		machines_usage[i].push_back(0);
	}

	start_times = new int*[jobs_c];
	for (int i = 0; i < jobs_c; ++i) start_times[i] = new int[machines_c];

	// storing best result's data
	int* best_start_times = new int[jobs_c];
	for (int i = 0; i < jobs_c; ++i) int* best_start_times = new int[machines_c];
	int best_time = MAXINT, curr_time;

	// choose order of jobs scheduling
	int* job_order = new int[jobs_c];

	while (!time_passed(start_stamp, time_limit))
	{
		for (int i = 0; i < jobs_c; ++i)
		{
			// clear machines usage I guess
			curr_time = fit_jobs(machines_c, jobs_c, proc_order, proc_times, start_times, machines_usage, job_order)

				//porownaj rozwiazanie z dotychczas najlepszym
		}
	}
	// TODO you could return start times of the best solution instead of passing it up there
}

int fit_jobs(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int**& start_times, std::vector<std::vector<int>> machines_usage, int* job_order)
/* schedule time for jobs according to job_order */
// if iteration is already started (some jobs are scheduled), don't put them in job_order and jobs_c
{
	for (int i = 0; i < jobs_c; ++i)
	{
		// wykonaj wybrany job
		exec_job(job_order[i], machines_c, proc_order[job_order[i]], proc_times[job_order[i]], start_times[job_order[i]], machines_usage);


	}
	// time of execution is max of last items of machines_usage's items
	int max_time = machines_usage[0].back();
	for (int i = 1; i < machines_c; ++i)
		if (machines_usage[i].back() > max_time) max_time = machines_usage[i].back();

	return max_time;
}

void exec_job(int job_no, int machines_c, int* proc_order, int* proc_times, int* start_times, std::vector<std::vector<int>> machines_usage)
/* schedule execution of each of job's tasks in first available time window */
{
	int machine_no, task_dur, last_ended = 0;
	bool scheduled;
	for (int i = 0; i < machines_c; ++i)
	{
		machine_no = proc_order[i];
		task_dur = proc_times[i];
		if (!task_dur)                                       // task duration is 0
			start_times[i] = last_ended;

		else if (machines_usage[machine_no].size() == 1)     // if no jobs assigned yet
		{
			start_times[i] = last_ended;
			machines_usage[machine_no].push_back(last_ended);
			machines_usage[machine_no].push_back(last_ended + task_dur);
		}
		else
		{
			scheduled = 0;
			for (int j = 1; j < machines_usage.size(); j += 2)
			{
				if ((machines_usage[machine_no][j] - machines_usage[machine_no][j - 1]) >= task_dur)
				{
					start_times[i] = machines_usage[machine_no][j + 1];
					machines_usage[machine_no][j] = machines_usage[machine_no][j - 1] + task_dur;
					scheduled = 1;
				}
			}
			if (!scheduled)
			{
				// start the task when possible - machine available or previous finished, whatever comes sooner
				if (machines_usage[machine_no].back() >= last_ended)
				{
					start_times[i] = machines_usage[machine_no][j + 1];
					machines_usage[machine_no][machines_usage[machine_no].size()] = machines_usage[machine_no].back() + task_dur;
				}
				else
				{
					start_times[i] = last_ended;
					machines_usage[machine_no].push_back(last_ended);
					machines_usage[machine_no].push_back(last_ended + task_dur);
				}

			}
		}
		last_ended = start_times[i] + task_dur;
	}
}
