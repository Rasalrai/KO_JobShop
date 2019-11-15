#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include "input_output.h"

void read_b(std::string filename, int* machines_c, int* jobs_c, int**& machines, int**& jobs, int max_jobs)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if(odczyt.good())
	{
	    std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> *jobs_c >> *machines_c;
		if (max_jobs) *jobs_c = max_jobs;
		// std::getline(odczyt, line);
		// std::getline(odczyt, line);

		machines = new int*[*jobs_c];
		jobs = new int*[*jobs_c];
		for (int i = 0; i < *jobs_c; ++i)
		{
			machines[i] = new int[*machines_c];
			jobs[i] = new int[*machines_c];
		}
	}

    for (int i = 0; i < *jobs_c; ++i)
    {
        for (int j = 0; j < 2 * (*machines_c); j+=2) {
            odczyt >> machines[i][j/2] >> jobs[i][j/2];
        }
    }
}

void read_t(std::string filename, int* machines_c, int* jobs_c, int**& machines, int**& jobs, int max_jobs)
{
	// TODO files in this format have additional lines
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> *jobs_c >> *machines_c;
		if (max_jobs) *jobs_c = max_jobs;
		/*
		std::getline(odczyt, line);
		std::getline(odczyt, line);
		*/

		machines = new int*[*jobs_c];
		jobs = new int*[*jobs_c];
		for (int i = 0; i < *jobs_c; ++i)
		{
			machines[i] = new int[*machines_c];
			jobs[i] = new int[*machines_c];
		}

		// read times
		for (int i = 0; i < *jobs_c; ++i)
			for (int j = 0; j < *machines_c; ++j)
			    odczyt >> jobs[i][j];
		// std::getline(odczyt, line);
		// read machines
		for (int i = 0; i < *jobs_c; ++i)
			for (int j = 0; j < *machines_c; ++j)
				odczyt >> machines[i][j];
		odczyt.close();
	}
}

void write_to_file(std::string filename, int machines_c, int jobs_c, int64_t**& times)
{
	/*
	Rozwiazanie podac w postaci: d³ugosc uszeregowania \n
	momenty_rozpoczêcia_wykonywania_kolejnych_operacji_zadania1 \n
	momenty_rozpoczêcia_wykonywania_kolejnych_operacji_zadania2 \n
	momenty_rozpoczêcia_wykonywania_kolejnych_operacji_zadania3 \n ...
	momenty_rozpoczêcia_wykonywania_kolejnych_operacji_ostatniego_zadania \n
	*/
	std::ofstream zapis;
	zapis.open(filename, std::ios::out);

	if (zapis.good())
	{
	    std::cout << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
        zapis << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
        std::cout << "Czasy:\n";
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
        std::cout << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
        zapis << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';

        zapis.close();
    }
}
