#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdint>
#include "input_output.h"

void read_b(std::string filename, int& machines_c, int& jobs_c, std::vector< std::vector<int> >& machines, std::vector< std::vector<int> >& jobs, int max_jobs)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if(odczyt.good())
	{
	    //std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> jobs_c >> machines_c;
		if (max_jobs && max_jobs < jobs_c) jobs_c = max_jobs;

		std::vector< std::vector<int> > machines(jobs_c);
		std::vector< std::vector<int> > jobs(jobs_c);
		for (int i = 0; i < jobs_c; ++i)
		{
			machines[i].resize(machines_c);
			jobs[i].resize(machines_c);
		}

        for (int i = 0; i < jobs_c; ++i)
        {
            for (int j = 0; j < 2 * (machines_c); j+=2) {
                odczyt >> machines[i][j/2] >> jobs[i][j/2];
            }
        }
    }
}

void read_t(std::string filename, int& machines_c, int& jobs_c, std::vector< std::vector<int> >& machines, std::vector< std::vector<int> >& jobs, int max_jobs)
{
	// TODO files in this format have additional lines
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		//std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> jobs_c >> machines_c;
		if (max_jobs && max_jobs < jobs_c) jobs_c = max_jobs;
		
		std::getline(odczyt, line);
		std::getline(odczyt, line);

		std::vector< std::vector<int> > machines(jobs_c);
		std::vector< std::vector<int> > jobs(jobs_c);
		for (int i = 0; i < jobs_c; ++i)
		{
			machines[i].resize(machines_c);
			jobs[i].resize(machines_c);
		}

		// read times
		for (int i = 0; i < jobs_c; ++i)
			for (int j = 0; j < machines_c; ++j)
			{
				odczyt >> jobs[i][j];
				//std::cout << jobs[i][j] << '\t';
			}
		//std::cout << "\n\n";
		odczyt.ignore();
		std::getline(odczyt, line);
		//std::cout << line << '\n';
		// read machines
		for (int i = 0; i < jobs_c; ++i)
			for (int j = 0; j < machines_c; ++j)
			{
				odczyt >> machines[i][j];
				machines[i][j]--;
				//std::cout << machines[i][j] << '\t';
			}
			/*for (int j = 0; j < machines_c; ++j)
				odczyt >> machines[i][j];*/
		odczyt.close();
	}
}

void write_to_file(std::string filename, int machines_c, int jobs_c, std::vector< std::vector<int64_t> > times)
{
	/*
	Rozwiazanie podac w postaci: d_ugosc uszeregowania \n
	momenty_rozpocz_cia_wykonywania_kolejnych_operacji_zadania1 \n
	momenty_rozpocz_cia_wykonywania_kolejnych_operacji_zadania2 \n
	momenty_rozpocz_cia_wykonywania_kolejnych_operacji_zadania3 \n ...
	momenty_rozpocz_cia_wykonywania_kolejnych_operacji_ostatniego_zadania \n
	*/
	std::ofstream zapis;
	zapis.open(filename, std::ios::out);

	if (zapis.good())
	{
	    //std::cout << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
        //zapis << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
        for (int i = 0; i < jobs_c; ++i)
        {
            for (int j = 0; j < machines_c; ++j)
            {
                std::cout << times[i][j] << "\t";
                zapis << times[i][j] << "\t";
            }
            std::cout << '\n';
            zapis << '\n';
        }
        zapis.close();
    }
}
