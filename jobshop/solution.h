#pragma once
#include <vector>

#define V_INT std::vector<int>
#define V_INT64 std::vector<int64_t>
#define V_V_INT std::vector< std::vector<int> >
#define V_V_INT64 std::vector< std::vector<int64_t> >

bool time_passed(time_t start, int limit);
V_V_INT64 js_init(int machines_c, int jobs_c, V_V_INT& proc_order, V_V_INT& proc_times, time_t start_stamp, int time_limit, int64_t& best_time);
V_V_INT64 go_through(int machines_c, int jobs_c, V_V_INT& proc_order, V_V_INT& proc_times, time_t start_stamp, int time_limit, V_V_INT64 machines_usage, V_V_INT& priority, V_V_INT64 start_times, V_V_INT64& best_start_times, int64_t best_time, V_INT job_order, std::vector<bool> jobs_scheduled, std::vector< std::pair<int, int64_t> >& quality);
V_V_INT64 job_shop(int machines_c, int jobs_c, V_V_INT& proc_order, V_V_INT& proc_times, time_t start_stamp, int time_limit, V_V_INT64 machines_usage, V_V_INT& priority, V_V_INT64 start_times, V_V_INT64& best_start_times, int64_t best_time, V_INT job_order, std::vector<bool> jobs_scheduled, std::vector< std::pair<int, int64_t> > quality);
int64_t fit_jobs(int machines_c, int jobs_c, V_V_INT& proc_order, V_V_INT& proc_times, V_V_INT64& start_times, V_V_INT64& machines_usage, V_INT job_order);
void exec_job(int job_no, int machines_c, std::vector<int>& proc_order, std::vector<int>& proc_times, std::vector<int64_t>& start_times, std::vector< std::vector<int64_t> >& machines_usage);
std::vector<int> job_ordering(std::vector<bool> jobs_scheduled);
int64_t check_iteration(int machines_c, int jobs_c, V_V_INT& proc_order, V_V_INT& proc_times, int job_no, int position, V_INT job_order, std::vector<bool> jobs_scheduled, V_V_INT64& start_times, V_V_INT64 machines_usage);
void get_priorities(V_INT& priorities, std::vector< std::pair<int, int64_t> > quality);
std::vector< std::vector<int64_t> > random_job_shop(int machines_c, int jobs_c, std::vector< std::vector<int> >& proc_order, std::vector< std::vector<int> >& proc_times, time_t start_stamp, int time_limit, int64_t& best_time);
void quickSort(std::vector< std::pair<int, int64_t> >& tab, int l, int r);
