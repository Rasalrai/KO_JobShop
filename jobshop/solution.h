#pragma once
void job_shop(int machines_c, int jobs_c, int**& proc_order, int**& proc_times, int**& start_times, time_t start_stamp, int time_limit);
bool check_time(time_t start, int limit);