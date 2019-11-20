#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <random>
#include "solution.h"
#define MU_MN machines_usage[machine_no]

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

	std::vector< std::vector<int64_t> >* p_times = &start_times, *p_best_times = &best_start_times, *p_temp;

	int64_t best_time = INT64_MAX, curr_time;

	// choose order of jobs scheduling
	std::vector<int> job_order(jobs_c);
	for (int i = 0; i < jobs_c; ++i) job_order[i] = i;

	//while (!time_passed(start_stamp, time_limit))
	{
//		while (!time_passed(start_stamp, time_limit))
        // clear machines usage
		for (int j = 0; j < machines_c; ++j) machines_usage[j].resize(1);
        for (int i = 0; i < 10; ++i)
		{
			curr_time = fit_jobs(machines_c, jobs_c, proc_order, proc_times, *p_times, machines_usage, job_order);
			// std::cout << curr_time << ' ';

			// compare with previous best
			if (curr_time < best_time)
			{
				best_time = curr_time;

				p_temp = p_best_times;
				p_best_times = p_times;
				p_times = p_temp;
				std::cout << "\t--" << curr_time << "--\n\n";
			}
			std::random_shuffle(job_order.begin(), job_order.end());
		}
	}
	std::cout << best_time << "\n\n";
	return *p_best_times;
}
int64_t fit_jobs(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, std::vector< std::vector<int64_t> >& start_times, std::vector< std::vector<int64_t> > machines_usage, std::vector<int> job_order)
{
	/* schedule time for jobs according to job_order */
	// this can also continue an already started combinations
	for (int i = 0; i < jobs_c; ++i)
		exec_job(job_order[i], machines_c, proc_order[job_order[i]], proc_times[job_order[i]], start_times[job_order[i]], machines_usage);

	for(int i=0;i<start_times.size();++i)
	{
	    for(int j=0;j<start_times[0].size();++j) std::cout << start_times[i][j] << '\t';
	    std::cout << "\n";
	}
	std::cout << "\n\n";

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

		else if (MU_MN.size() == 1)     // if no jobs assigned yet: allocate as soon as the previous task has ended
		{
			if (last_ended)
			{
				start_times[i] = last_ended;
				MU_MN.push_back(last_ended);
				MU_MN.push_back(last_ended + task_dur);
			}
			else
			{
				MU_MN[0] = task_dur;
				start_times[i] = 0;
			}
		}
		else
		{
			scheduled = 0;
			// search for an available window for this
			// you can put it either right after previous task done by this machine, or some time after
			// TODO binary search for the first available window
			// for (std::vector<int64_t>::iterator j = machines_usage[machine_no].begin() + 1; j <= machines_usage[machine_no].end(); j += 2)
			for (int j = MU_MN[0] + 1; j < MU_MN.size(); j += 2)
			{
				if (task_dur <= (MU_MN[j] - MU_MN[j-1]) && task_dur <= (MU_MN[j] - last_ended))
					//fits into window and is after previous task
				{
					if (last_ended <= MU_MN[j-1])
					{
						// execute this task as soon as the machine is free
						start_times[i] = MU_MN[j-1];
						MU_MN[j-1] += task_dur;
						scheduled = 1;
						break;
					}
					else
					{
						// execute later -> need to insert into vector
						start_times[i] = last_ended;
						if (task_dur == (MU_MN[j] - last_ended))
						{
							MU_MN[j] = last_ended;
						}
						else
						{
							MU_MN.insert(MU_MN.begin()+j, 2, last_ended);
							MU_MN[j+1] += task_dur;
							scheduled = 1;
							break;
						}
					}
				}
			}
			if (!scheduled)
			{
				// start the task when possible - machine available or previous finished, whatever comes later
				if (MU_MN.back() >= last_ended)
				{
					start_times[i] = MU_MN.back();
					// machines_usage[machine_no][machines_usage[machine_no].size()] = machines_usage[machine_no].back() + task_dur;
					//increase last element by task_dur
					*(MU_MN.end() - 1) += task_dur;
				}
				else
				{
					start_times[i] = last_ended;
					MU_MN.push_back(last_ended);
					MU_MN.push_back(last_ended + task_dur);
				}
			}
		}
		last_ended = start_times[i] + task_dur;
	}
}
