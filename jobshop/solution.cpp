#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include "solution.h"

#define INT64_MAX 9223372036854775807i64

bool time_passed(time_t start, int limit)
/* true if _limit_ minutes passed since beginning of execution of the program */
{
	if (time(NULL) >= start + 60 * limit)
		return true;
	return false;
}

int64_t** job_shop(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, time_t start_stamp, int time_limit)
{
	// storing iterations' data
	std::vector<std::vector<int64_t>> machines_usage(machines_c);
	for (int i = 0; i < machines_c; ++i)
	{
		machines_usage[i].reserve(jobs_c * 2);
		machines_usage[i].push_back(0);
	}

	int64_t** start_times = new int64_t*[jobs_c];
	for (int i = 0; i < jobs_c; ++i) start_times[i] = new int64_t[machines_c];

	// storing best result's data
	int64_t** best_start_times = new int64_t*[jobs_c];
	for (int i = 0; i < jobs_c; ++i) best_start_times[i] = new int64_t[machines_c];
	int64_t best_time = INT64_MAX, curr_time;
	int64_t** tmp;

	// choose order of jobs scheduling
	int* job_order = new int[jobs_c];
	for (int i = 0; i < jobs_c; ++i) job_order[i] = i;

	//while (!time_passed(start_stamp, time_limit))
	{
		while (!time_passed(start_stamp, time_limit))
		//for (int i = 0; i < jobs_c*90000; ++i)
		{
			// clear machines usage
			for (int j = 0; j < machines_c; ++j)
				machines_usage[j].resize(1);

			curr_time = fit_jobs(machines_c, jobs_c, proc_order, proc_times, start_times, machines_usage, job_order);
			// std::cout << curr_time << ' ';

			//porownaj rozwiazanie z dotychczas najlepszym
			if (curr_time < best_time)
			{
				best_time = curr_time;

				tmp = best_start_times;
				best_start_times = start_times;
				start_times = tmp;
				//std::cout << curr_time << ' ';
			}

			// new order
			/*job_order[0] = job_order[0] ^ job_order[i + 1];
			job_order[i + 1] = job_order[0] ^ job_order[i + 1];
			job_order[0] = job_order[0] ^ job_order[i + 1];*/
			std::random_shuffle(job_order, job_order + jobs_c);
		}
	}
	// TODO you could return start times of the best solution instead of passing it up there
	//std::cout << "\n" << best_time << "\n";
	return best_start_times;
}

int64_t fit_jobs(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int64_t**& start_times, std::vector<std::vector<int64_t>>& machines_usage, int* job_order)
/* schedule time for jobs according to job_order */
// if iteration is already started (some jobs are scheduled), don't put them in job_order and jobs_c
{
	for (int i = 0; i < jobs_c; ++i)
	{
		// wykonaj wybrany job
		exec_job(job_order[i], machines_c, proc_order[job_order[i]], proc_times[job_order[i]], start_times[job_order[i]], machines_usage);
	}
	// time of execution is max of last items of machines_usage's items
	int64_t max_time = machines_usage[0].back();
	for (int i = 1; i < machines_c; ++i)
		if (machines_usage[i].back() > max_time) max_time = machines_usage[i].back();

	return max_time;
}

void exec_job(int job_no, int machines_c, int* proc_order, int* proc_times, int64_t* start_times, std::vector<std::vector<int64_t>>& machines_usage)
/* schedule execution of each of job's tasks in first available time window */
{
	int machine_no, task_dur;
	int64_t last_ended = 0;
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
			for (int j = 1; j < machines_usage[machine_no].size(); j += 2)
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
				// start the task when possible - machine available or previous finished, whatever comes later
				if (machines_usage[machine_no].back() >= last_ended)
				{
					start_times[i] = machines_usage[machine_no].back();
					// machines_usage[machine_no][machines_usage[machine_no].size()] = machines_usage[machine_no].back() + task_dur;
					//increase last element by task_dur
					*(machines_usage[machine_no].end()-1) += task_dur;
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
