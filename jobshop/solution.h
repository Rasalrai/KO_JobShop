#pragma once
#include <vector>

bool time_passed(time_t start, int limit);
std::vector< std::vector<int64_t> > job_shop(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, time_t start_stamp, int time_limit);
int64_t fit_jobs(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, std::vector< std::vector<int64_t> >& start_times, std::vector< std::vector<int64_t> > machines_usage, std::vector<int> job_order);
void exec_job(int job_no, int machines_c, std::vector<int>& proc_order, std::vector<int>& proc_times, std::vector<int64_t>& start_times, std::vector< std::vector<int64_t> >& machines_usage);
void job_ordering(std::vector<int>* begin, std::vector<int>* end);
std::vector< std::vector<int64_t> > random_job_shop(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, time_t start_stamp, int time_limit);
