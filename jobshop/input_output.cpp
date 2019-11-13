#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include "constants.h"

void read_b(std::string filename)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if(odczyt.good())
	{
	    std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> JOBS_COUNT >> MACHINES_COUNT;
		// std::getline(odczyt, line);
		// std::getline(odczyt, line);

		MACHINES_ORDER = new int*[JOBS_COUNT];
		JOB_DUR_TIMES = new int*[JOBS_COUNT];
		for (int i = 0; i < JOBS_COUNT; ++i)
		{
			MACHINES_ORDER[i] = new int[MACHINES_COUNT];
			JOB_DUR_TIMES[i] = new int[MACHINES_COUNT];
		}
	}

    for (int i = 0; i < JOBS_COUNT; ++i)
    {
        for (int j = 0; j < 2 * MACHINES_COUNT; j+=2) {
            odczyt >> MACHINES_ORDER[i][j/2] >> JOB_DUR_TIMES[i][j/2];
            std::cout << MACHINES_ORDER[i][j/2] << "\t" << JOB_DUR_TIMES[i][j/2] << "\t";
        }
        std::cout<<"\n";
    }
    std::cout << "\n\n\n\n";
}

void read_t(std::string filename)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> JOBS_COUNT >> MACHINES_COUNT;
		/*
		std::getline(odczyt, line);
		std::getline(odczyt, line);
		*/

		MACHINES_ORDER = new int*[JOBS_COUNT];
		JOB_DUR_TIMES = new int*[JOBS_COUNT];
		for (int i = 0; i < JOBS_COUNT; ++i)
		{
			MACHINES_ORDER[i] = new int[MACHINES_COUNT];
			JOB_DUR_TIMES[i] = new int[MACHINES_COUNT];
		}

		// read times
		for (int i = 0; i < JOBS_COUNT; ++i)
			for (int j = 0; j < MACHINES_COUNT; ++j)
			{
			    odczyt >> JOB_DUR_TIMES[i][j];
			    std::cout << JOB_DUR_TIMES[i][j] << '\t';
			}
		// std::getline(odczyt, line);
		// read machines
		std::cout << '\n';
		int x;
		for (int i = 0; i < JOBS_COUNT; ++i)
		 {
			for (int j = 0; j < MACHINES_COUNT; ++j)
			{
				odczyt >> x;
				MACHINES_ORDER[i][j] = x;
				std::cout << MACHINES_ORDER[i][j] << "\t";
			}
		}
		odczyt.close();
	}
}

void write_to_file(std::string filename)
{
	std::ofstream zapis;
	zapis.open(filename, std::ios::out);

	if (zapis.good())
	{
	    std::cout << "machines count " << MACHINES_COUNT << '\n' << "jobs count " << JOBS_COUNT << '\n';
        zapis << "machines count " << MACHINES_COUNT << '\n' << "jobs count " << JOBS_COUNT << '\n';
        std::cout << "Maszyny:\n";
        for (int i = 0; i < JOBS_COUNT; ++i)
        {
            for (int j = 0; j < MACHINES_COUNT; ++j)
            {
                std::cout << MACHINES_ORDER[i][j] << "\t";
                zapis << MACHINES_ORDER[i][j] << "\t";
            }
            std::cout << '\n';
            zapis << '\n';
        }
        std::cout << "Czasy:\n";
        for (int i = 0; i < JOBS_COUNT; i++)
        {
            for (int j = 0; j < MACHINES_COUNT; j++)
            {
                std::cout << JOB_DUR_TIMES[i][j] << "\t";
                zapis << JOB_DUR_TIMES[i][j] << "\t";
            }
            std::cout << '\n';
            zapis << '\n';
        }
        std::cout << "machines count " << MACHINES_COUNT << '\n' << "jobs count " << JOBS_COUNT << '\n';
        zapis << "machines count " << MACHINES_COUNT << '\n' << "jobs count " << JOBS_COUNT << '\n';

        zapis.close();
    }
}
