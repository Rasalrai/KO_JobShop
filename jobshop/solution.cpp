#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "solution.h"

bool time_passed(time_t start, int limit)
/* true if _limit_ minutes passed since beginning of execution of the program */
{
	if (time(NULL) >= start + 60 * limit)
		return true;
	return false;
}

std::vector< std::vector<int64_t> > job_shop(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, time_t start_stamp, int time_limit)
{
	// storing iterations' data
	std::vector< std::vector<int64_t> > machines_usage(machines_c);
	for (int i = 0; i < machines_c; ++i)
	{
		machines_usage[i].reserve(jobs_c * 2);
		machines_usage[i].push_back(0);
	}

	std::vector< std::vector<int64_t> > start_times(jobs_c);
	std::vector< std::vector<int64_t> > best_start_times(jobs_c);
	for (int i = 0; i < jobs_c; ++i)
	{
	    start_times[i].resize(machines_c);
	    best_start_times[i].resize(machines_c);
	}

	std::vector< std::vector<int64_t> >* p_times = &start_times, * p_best_times = &best_start_times, *p_temp;

	int64_t best_time = INT64_MAX, curr_time;

	// choose order of jobs scheduling
	std::vector<int> job_order(jobs_c);
	for (int i = 0; i < jobs_c; ++i) job_order[i] = i;

	//while (!time_passed(start_stamp, time_limit))
	{
		while (!time_passed(start_stamp, time_limit))
		{
			// clear machines usage
			for (int j = 0; j < machines_c; ++j)
				machines_usage[j].resize(1);

			curr_time = fit_jobs(machines_c, jobs_c, proc_order, proc_times, *p_times, machines_usage, job_order);
			// std::cout << curr_time << ' ';

			// compare with previous best
			if (curr_time < best_time)
			{
				best_time = curr_time;

				p_temp = p_best_times;
				p_best_times = p_times;
				p_times = p_best_times;
				//std::cout << curr_time << ' ';
			}
			std::random_shuffle(job_order.begin(), job_order.end());
		}
	}
	//std::cout << "\n" << best_time << "\n";
	return *p_best_times;
}
int64_t fit_jobs(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, std::vector< std::vector<int64_t> >& start_times, std::vector< std::vector<int64_t> >& machines_usage, std::vector<int> job_order)
{
/* schedule time for jobs according to job_order */
// this can also continue an already started combinations
	for (int i = 0; i < jobs_c; ++i)
	    exec_job(job_order[i], machines_c, proc_order[job_order[i]], proc_times[job_order[i]], start_times[job_order[i]], machines_usage);

	// time of execution is max of last items of machines_usage's items
	int64_t max_time = machines_usage[0].back();
	for (int i = 1; i < machines_c; ++i)
		if (machines_usage[i].back() > max_time) max_time = machines_usage[i].back();

	return max_time;
}

void exec_job(int job_no, int machines_c, std::vector<int>& proc_order, std::vector<int>& proc_times, std::vector<int64_t>& start_times, std::vector< std::vector<int64_t> >& machines_usage)
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
