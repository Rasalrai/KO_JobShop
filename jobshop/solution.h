#pragma once
void job_shop(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int**& start_times, time_t start_stamp, int time_limit);
bool time_passed(time_t start, int limit);
int fit_jobs(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int**& start_times, int* done, std::vector<std::vector<int>> machines_usage);
void exec_job(int job_no, int machines_c, int jobs_c, int* proc_order, int* proc_times, int* start_times, std::vector<std::vector<int>> machines_usage);