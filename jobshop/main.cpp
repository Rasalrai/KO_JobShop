#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

void read_t(std::string filename, int* machinesCount, int* jobsCount);
void read_b(std::string filename, int* machinesCount, int* jobsCount);
void write_to_file(std::string filename, int* machinesCount, int* jobsCount);

int** maszyny;
int** czasy;

// TODO: add argument to limit number of instances to solve from file
/*
argv:
	[1] inFileName
	[2] fileType
		t - Taillard's format
		b - Beasley's format (orlib)
*/
int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);
	std::string inFileName = argv[1];
	std::string fileType = argv[2];

	
	int machinesCount, jobsCount;

	std::cout << "filename: " << inFileName << ", type: " << fileType << '\n';

	if (fileType[0] == 't')
	{
	    read_t(inFileName, &machinesCount, &jobsCount);
	    write_to_file("wynik_t.txt", &machinesCount, &jobsCount);
	}

	else if (fileType[0] == 'b')
	{
		read_b(inFileName, &machinesCount, &jobsCount);
        write_to_file("wynik_b.txt", &machinesCount, &jobsCount);
	}
	else
	    std::cout << "blad\n";

	return 0;
}

void read_b(std::string filename, int* machinesCount, int* jobsCount)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if(odczyt.good())
	{
	    std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> (*jobsCount) >> (*machinesCount);
		// std::getline(odczyt, line);
		// std::getline(odczyt, line);

		maszyny = new int*[*jobsCount];
		czasy = new int*[*jobsCount];
		for (int i = 0; i < (*jobsCount); ++i)
		{
			maszyny[i] = new int[*machinesCount];
			czasy[i] = new int[*machinesCount];
		}
	}

    for (int i = 0; i < (*jobsCount); ++i)
    {
        for (int j = 0; j < 2 * (*machinesCount); j+=2) {
            odczyt >> maszyny[i][j/2] >> czasy[i][j/2];
            std::cout << maszyny[i][j/2] << "\t" << czasy[i][j/2] << "\t";
        }
        std::cout<<"\n";
    }
    std::cout << "\n\n\n\n";

}

void read_t(std::string filename, int* machinesCount, int* jobsCount)
{
	std::ifstream odczyt;
	std::string line;

	odczyt.open(filename, std::ios::in);
	if (odczyt.good())
	{
		std::cout << "Udalo sie otworzyc" << '\n';

		odczyt >> (*jobsCount) >> (*machinesCount);
		/*
		std::getline(odczyt, line);
		std::cout << line << '\n';
		std::getline(odczyt, line);
		std::cout << line<<"\n\n";
		*/

		maszyny = new int*[*jobsCount];
		czasy = new int*[*jobsCount];
		for (int i = 0; i < (*jobsCount); ++i)
		{
			maszyny[i] = new int[*machinesCount];
			czasy[i] = new int[*machinesCount];
		}

		// read times
		for (int i = 0; i < (*jobsCount); ++i)
			for (int j = 0; j < (*machinesCount); ++j)
			{
			    odczyt >> czasy[i][j];
			    std::cout << czasy[i][j] << '\t';
			}

		// std::getline(odczyt, line);
		// std::cout << line<<"\n\n";
		// read machines
		std::cout << '\n';
		int x;
		for (int i = 0; i < (*jobsCount); ++i)
		 {
			for (int j = 0; j < (*machinesCount); ++j)
			{
				odczyt >> x;
				maszyny[i][j] = x;
				std::cout << maszyny[i][j] << "\t";
			}
			// std::cout << '\n';
		}
		odczyt.close();
	}
}

void write_to_file(std::string filename, int* machinesCount, int* jobsCount)
{
	std::ofstream zapis;
	zapis.open(filename, std::ios::out);

	if (zapis.good())
	{
	    std::cout << "machines count " << (*machinesCount) << '\n' << "jobs count " << (*jobsCount) << '\n';
        zapis << "machines count " << (*machinesCount) << '\n' << "jobs count " << (*jobsCount) << '\n';
        std::cout << "Maszyny:\n";
        std::cout << "1";
        for (int i = 0; i < (*jobsCount); ++i)
        {
            std::cout << "2";
            for (int j = 0; j < (*machinesCount); ++j)
            {
                std::cout << maszyny[i][j] << "\t";
                zapis << maszyny[i][j] << "\t";
            }
            std::cout << '\n';
            zapis << '\n';
        }
        std::cout << "Czasy:\n";
        for (int i = 0; i < (*jobsCount); i++)
        {
            for (int j = 0; j < (*machinesCount); j++)
            {
                std::cout << czasy[i][j] << "\t";
                zapis << czasy[i][j] << "\t";
            }
            std::cout << '\n';
            zapis << '\n';
        }
        std::cout << "machines count " << (*machinesCount) << '\n' << "jobs count " << (*jobsCount) << '\n';
        zapis << "machines count " << (*machinesCount) << '\n' << "jobs count " << (*jobsCount) << '\n';

        zapis.close();
    }
}
