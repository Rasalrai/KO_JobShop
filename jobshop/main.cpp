#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

void read_t(std::string filename);
void read_b(std::string filename);
void write_to_file(int** maszyny, int** czasy, std::string filename);

int main(int argc, char *argv[])
// TODO: add argument to limit number of instances to solve from file
/*
argv:
	[1] inFileName
	[2] fileType
		t - Taillard's format
		b - Beasley's format (orlib)
*/
{
	std::ios_base::sync_with_stdio(false);
	std::ifstream odczyt;
	std::ofstream zapis;
	int machinesCount;
	int jobsCount;
	int mCount = 0;
	int jCount = 0;
	std::string inFileName = argv[1];
	std::string fileType = argv[2];
	std::string line;

	std::cout << "filename: " << inFileName << ", type: " << fileType << '\n';

	odczyt.open(inFileName, std::ios::in);
	if (fileType == "t")
		read_t();

	else if (fileType == "b")
	{
		if (odczyt.good())
		{
			std::cout << "brawo" << '\n';

			do
			{
				std::getline(odczyt, line);
			} while (line[0] != ' ' and line[1] != '+');
			std::getline(odczyt, line);
			odczyt >> jobsCount >> machinesCount;

			int** maszyny = new int*[jobsCount];
			int** czasy = new int*[jobsCount];

			/*
			odczyt >> machinesCount;
			odczyt >> jobsCount;

			int** maszyny = new int* [machinesCount];
			for (int i = 0; i < jobsCount; i++)
			{
				maszyny[i] = new int[machinesCount];
			}

			int** czasy = new int* [jobsCount];
			for (int i = 0; i < jobsCount; i++)
			{
				czasy[i] = new int[machinesCount];
			}

			for (int i = 0; i < jobsCount; i++)
			{
				for (int j = 0; j < machinesCount; j++)
				{
					odczyt >> czasy[i][j];
				}
			}

			for (int i = 0; i < jobsCount; i++)
			{
				for (int j = 0; j < machinesCount; j++)
				{
					odczyt >> maszyny[i][j];
				}
			}

			*/
			odczyt.close();

			zapis.open("wynik1.txt", std::ios::out);
			if (zapis.good())
			{
				zapis << jobsCount << " ";
				zapis << machinesCount << "\n";
				for (int i = 0; i < jobsCount; i++)
				{
					for (int j = 0; j < machinesCount; j++)
					{
						zapis << czasy[i][j] << " ";
					}
					zapis << "\n";
				}
				for (int i = 0; i < jobsCount; i++)
				{
					for (int j = 0; j < machinesCount; j++)
					{
						zapis << maszyny[i][j] << " ";
					}
					zapis << "\n";
				}
				zapis.close();
			}
		}
	}
	else
	{
		std::cout << "blad\n";
	}
	return 0;

}

void read_b(std::string filename)
{
	std::ifstream odczyt;
	std::ofstream zapis;
	int machinesCount;
	int jobsCount;
	std::string line;


	std::ifstream odczyt;
	odczyt.open(filename, std::ios::in);



}

void read_t(std::string filename)
{
	std::ifstream odczyt;
	std::ofstream zapis;
	int machinesCount;
	int jobsCount;
	std::string line;


	std::ifstream odczyt;
	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> jobsCount >> machinesCount;
		std::getline(odczyt, line);
		std::getline(odczyt, line);

		int** maszyny = new int*[jobsCount];
		int** czasy = new int*[jobsCount];
		for (int i = 0; i < jobsCount; ++i)
		{
			maszyny[i] = new int[machinesCount];
			czasy[i] = new int[machinesCount];
		}

		// read times
		for (int i = 0; i < jobsCount; ++i)
			for (int j = 0; j < machinesCount; ++j)
				odczyt >> czasy[i][j];
		std::getline(odczyt, line);
		// read machines
		int x;
		for (int i = 0; i < jobsCount; ++i)
			for (int j = 0; j < machinesCount; ++j)
			{
				odczyt >> x;
				maszyny[i][j] = x;
			}
		// odczyt >> maszyny[i][j];

		/*
		odczyt >> machinesCount;
		odczyt >> jobsCount;

		int** maszyny = new int* [jobsCount];
		for (int i = 0; i < jobsCount; i++)
		{
			maszyny[i] = new int[machinesCount];
		}

		int** czasy = new int* [jobsCount];
		for (int i = 0; i < jobsCount; i++)
		{
			czasy[i] = new int[machinesCount];
		}

		for (int i = 0; i < jobsCount; i++)
		{
			for (int j = 0; j < (2 * machinesCount); j++)
			{
				if (j % 2 == 0)
				{
					odczyt >> maszyny[i][mCount];
					mCount++;
				}
				else
				{
					odczyt >> czasy[i][jCount];
					jCount++;
				}
			}
			mCount = 0;
			jCount = 0;
		}
		*/
		odczyt.close();
	}
}

void write_to_file(int** maszyny, int** czasy, std::string filename)
{
	std::ofstream zapis;
	int machinesCount;
	int jobsCount;
	zapis.open(filename, std::ios::out);

	if (zapis.good())
	std::cout << "Maszyny:" << '\n';
	for (int i = 0; i < jobsCount; ++i)
	{
		for (int j = 0; j < machinesCount; ++j)
		{
			std::cout << maszyny[i][j] << "\t";
			zapis << maszyny[i][j] << "\t";
		}
		std::cout << '\n';
		zapis << '\n';
	}
	std::cout << "Czasy:" << '\n';
	for (int i = 0; i < jobsCount; i++)
	{
		for (int j = 0; j < machinesCount; j++)
		{
			std::cout << czasy[i][j] << "\t";
			zapis << czasy[i][j] << "\t";
		}
		std::cout << '\n';
		zapis << '\n';
	}
	std::cout << "machines count " << machinesCount << '\n' << "jobs count " << jobsCount << '\n';
	zapis << "machines count " << machinesCount << '\n' << "jobs count " << jobsCount << '\n';

	zapis.close();
}