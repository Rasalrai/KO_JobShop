#pragma once
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

void read_t(std::string filename, int* machines_c, int* jobs_c, int**& machines, int**& jobs, int max_jobs);
void read_b(std::string filename, int* machines_c, int* jobs_c, int**& machines, int**& jobs, int max_jobs);
void write_to_file(std::string filename, int machines_c, int jobs_c, int64_t**& times);
