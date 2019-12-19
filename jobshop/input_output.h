#pragma once
#include <vector>
#include <iostream>
#include <cstdint>

void read_b(std::string& filename, int& machines_c, int& jobs_c, std::vector< std::vector<int> >& machines, std::vector< std::vector<int> >& jobs);
void read_t(std::string& filename, int& machines_c, int& jobs_c, std::vector< std::vector<int> >& machines, std::vector< std::vector<int> >& jobs);
void write_to_file(std::string& filename, int& machines_c, int& jobs_c, int64_t& end_time, std::vector< std::vector<int64_t> >& times, int& max_tasks);
