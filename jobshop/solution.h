#pragma once
#include <vector>
bool time_passed(time_t start, int limit);
int64_t** job_shop(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, time_t start_stamp, int time_limit);
int64_t fit_jobs(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int64_t**& start_times, std::vector<std::vector<int64_t>>& machines_usage, int* job_order);
void exec_job(int job_no, int machines_c, int* proc_order, int* proc_times, int64_t* start_times, std::vector<std::vector<int64_t>>& machines_usage);