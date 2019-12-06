#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "input_output.h"

void read_b(std::string filename, int& machines_c, int& jobs_c, std::vector< std::vector<int> >& machines, std::vector< std::vector<int> >& times)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		//std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> jobs_c >> machines_c;

		machines.resize(jobs_c);
		times.resize(jobs_c);
		for (int i = 0; i < jobs_c; ++i)
		{
			machines[i].resize(machines_c);
			times[i].resize(machines_c);
		}

		for (int i = 0; i < jobs_c; ++i)
		{
			for (int j = 0; j < (machines_c); ++j)
			{
				odczyt >> machines[i][j] >> times[i][j];
			}
		}
		odczyt.close();
	}
}

void read_t(std::string filename, int& machines_c, int& jobs_c, std::vector< std::vector<int> >& machines, std::vector< std::vector<int> >& times)
{
	int x;
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		//std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> jobs_c >> machines_c;

		std::getline(odczyt, line);
		std::getline(odczyt, line);

		machines.resize(jobs_c);
		times.resize(jobs_c);
		for (int i = 0; i < jobs_c; ++i)
		{
			machines[i].resize(machines_c);
			times[i].resize(machines_c);
		}

		// read times
		for (int i = 0; i < jobs_c; ++i)
			for (int j = 0; j < machines_c; ++j)
			{
				odczyt >> times[i][j];
				//std::cout << times[i][j] << '\t';
			}
		//std::cout << "\n\n";
		odczyt.ignore();
		std::getline(odczyt, line); odczyt.ignore();
		//std::cout << line << '\n';
		// read machines
		std::getline(odczyt, line); odczyt.ignore();
		for (int i = 0; i < jobs_c; ++i)
			for (int j = 0; j < machines_c; ++j)
			{
				odczyt >> x; --x;
				machines[i][j] = x;
				//std::cout << machines[i][j] << '\t';
			}
		/*for (int j = 0; j < machines_c; ++j)
			odczyt >> machines[i][j];*/
		odczyt.close();
	}
}

void write_to_file(std::string filename, int machines_c, int jobs_c, int64_t end_time, std::vector< std::vector<int64_t> > times, int max_tasks)
{
	/*
	Rozwiazanie podac w postaci: d_ugosc uszeregowania \n
	momenty_rozpoczecia_wykonywania_kolejnych_operacji_zadania1 \n
	momenty_rozpoczecia_wykonywania_kolejnych_operacji_zadania2 \n
	momenty_rozpoczecia_wykonywania_kolejnych_operacji_zadania3 \n ...
	momenty_rozpoczecia_wykonywania_kolejnych_operacji_ostatniego_zadania \n
	*/
	std::ofstream zapis;
	zapis.open(filename, std::ios::out);

	if (zapis.good())
	{
		std::cout << end_time << "\n";
		zapis << end_time << "\n";
		/*
		//std::cout << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
		//zapis << "machines count " << machines_c << '\n' << "jobs count " << jobs_c << '\n';
		*/
		for (int i = 0; i < jobs_c; ++i)
		{
			for (int j = 0; j < max_tasks; ++j)
			{
				//std::cout << times[i][j] << "\t";
				zapis << times[i][j] << "\t";
			}
			//std::cout << '\n';
			zapis << '\n';
		}
		zapis.close();
	}
}
