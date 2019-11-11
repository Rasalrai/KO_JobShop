#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main()
{
	fstream odczyt;
	fstream zapis;
	int machinesCount;
	int jobsCount;
	int mCount = 0;
	int jCount = 0;
	char name[10];
	char typ;
	cout << "Podaj typ pliku:\n";
	cin >> typ;
	cout << "Podaj nazwe pliku:\n";
	cin >> name;
	odczyt.open(name, ios::in);
	if (typ == 'b')
	{
		if (odczyt.good() == true)
		{
			cout << "Udalo sie otworzyc" << endl;
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
			odczyt.close();
			cout << "Maszyny:" << endl;
			for (int i = 0; i < jobsCount; i++)
			{
				for (int j = 0; j < machinesCount; j++)
				{
					cout << maszyny[i][j] << "\t";
				}
				cout << endl;
			}
			cout << "Czasy:" << endl;
			for (int i = 0; i < jobsCount; i++)
			{
				for (int j = 0; j < machinesCount; j++)
				{
					cout << czasy[i][j] << "\t";
				}
				cout << endl;
			}
			cout << "machines count " << machinesCount << endl;
			cout << "jobs count " << jobsCount << endl;

			zapis.open("wynik.txt", ios::out);
			if (zapis.good() == true)
			{
				zapis << jobsCount << " ";
				zapis << machinesCount << "\n";
				for (int i = 0; i < jobsCount; i++)
				{
					for (int j = 0; j < machinesCount; j++)
					{
						zapis << maszyny[i][j] << " ";
					}
					zapis << "\n";
				}
				for (int i = 0; i < jobsCount; i++)
				{
					for (int j = 0; j < machinesCount; j++)
					{
						zapis << czasy[i][j] << " ";
					}
					zapis << "\n";
				}
				zapis.close();
			}
		}
	}
	else if (typ == 't')
	{
		if (odczyt.good() == true)
		{
			cout << "brawo" << endl;
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
			odczyt.close();

			zapis.open("wynik1.txt", ios::out);
			if (zapis.good() == true)
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
		cout << "blad\n";
	}
	return 0;

}
