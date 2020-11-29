#include <iostream>
#include <fstream>
#include <stdio.h>
#include<cstdlib>
#include <ctime>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void main()
{
	srand(time(NULL));

	int z1, z2; //pozycje do podmiany
	int n = 0; //liczba zadan
	int m = 0; //liczba maszyn
			   //	int ** d; //czas pracy danego zadania na danej maszynie
			   //	int ** d1;
			   //	int ** d2; //czas pracy danego zadania na danej maszynie po zamianie - d1, nalepsz1 ustawienie - d2
			   //	int *S, *S1; // Czasy zakoñczenia
	int C, C1, Cpos, Cmax; //drogi krytyczne
	double T = 1000;
	double Tk = 0.005;
	double a = 0.99;
	double p, q;
	int delta;

	FILE* plik;
	plik = fopen("D:\\pwr\\NEH3.dat", "r");

	fscanf(plik, "%d", &n);
	fscanf(plik, "%d", &m);

	int **d = new int *[n + 1];
	int **d1 = new int *[n + 1];
	int **d2 = new int *[n + 1];
	int *S = new int[m + 1];
	int *S1 = new int[m + 1];

	for (int i = 0; i < n + 1; i++)
	{
		d[i] = new int[m + 1];
		d1[i] = new int[m + 1];
		d2[i] = new int[m + 1];
	}

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			d[i][j] = 0;
			d1[i][j] = 0;
			d2[i][j] = 0;
		}
	}



	for (int i = 0; i < n + 1; i++)
	{

		for (int j = 0; j < m + 1; j++)
		{
			if (i == 0)
			{
				d[i][j] = j;
			}
			else
			{
				if (j == 0)
				{
					d[i][j] = i;
				}
				else
				{
					fscanf(plik, "%d", &d[i][j]);
				}
			}
		}
	}



	fclose(plik);

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			cout << d[i][j] << " ";
		}
		cout << endl;
	}

	for (int j = 0; j < m + 1; j++)
		S[j] = 0;


	for (int i = 1; i<n + 1; i++) //liczenie trasy podstawowej
	{
		for (int j = 1; j < m + 1; j++)
		{
			if (S[j - 1] > S[j])
			{
				S[j] = d[i][j] + S[j - 1];
			}
			else
			{
				S[j] = d[i][j] + S[j];
			}
			cout << S[j] << " ";
		}
		cout << endl;
	}

	Cmax = S[m];
	Cpos = Cmax;


	while (T >= Tk)
	{

		for (int j = 0; j < m + 1; j++)
		{
			S[j] = 0;
			S1[j] = 0;
		}


		for (int i = 1; i<n + 1; i++) //liczenie trasy podstawowej
		{
			for (int j = 1; j < m + 1; j++)
			{
				if (S[j - 1] > S[j])
				{
					S[j] = d[i][j] + S[j - 1];
				}
				else
				{
					S[j] = d[i][j] + S[j];
				}
			}
		}

		C = S[m];

		z1 = rand() % n + 1; //losowanie liczb do zamiany
		z2 = rand() % n + 1;

		if (z1 < z2) { //zamiana liczb
			for (int i = 0; i < z1; i++)
			{
				d1[i] = d[i];
			}
			for (int i = z1; i < z2; i++)
			{
				d1[i] = d[i + 1];
			}
			d1[z2] = d[z1];
			for (int i = z2 + 1; i <= n; i++)
			{
				d1[i] = d[i];
			}
		}
		else {
			for (int i = 0; i < z2; i++)
			{
				d1[i] = d[i];
			}
			for (int i = z2; i < z1; i++)
			{
				d1[i] = d[i + 1];
			}
			d1[z1] = d[z2];
			for (int i = z1 + 1; i <= n; i++)
			{
				d1[i] = d[i];
			}
		}

		for (int i = 1; i<n + 1; i++) //liczenie trasy podstawowej
		{
			for (int j = 1; j < m + 1; j++)
			{
				if (S1[j - 1] > S1[j])
				{
					S1[j] = d1[i][j] + S1[j - 1];
				}
				else
				{
					S1[j] = d1[i][j] + S1[j];
				}
			}
		}

		C1 = S1[m];

		if (C1 < Cmax) //podmiana najlepszej
		{
			Cmax = C1;
			for (int j = 0; j < n + 1; j++)
			{
				d2[j] = d1[j];
			}
		}

		delta = C1 - C;
		if (delta <= 0) {
			for (int j = 0; j <= n; j++)
			{
				d[j] = d1[j];
			}
		}
		else {
			p = exp(-delta / T);
			q = rand() % 1;
			if (q < p) {
				for (int j = 0; j <= n; j++)
				{
					d[j] = d1[j];
				}
			}

		}
		T = a*T;

	}

	cout << "Cmax " << Cmax << endl;

	cout << "Cpos " << Cpos << endl;

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			cout << d2[i][j] << " ";
		}
		cout << endl;
	}

	system("pause");

	// zwalnianie pamieci
	/* for (int i = 0; i < n + 1; i++)
	{
	delete[] d[i];
	delete[] d1[i];
	delete[] d2[i];
	}

	delete[] d;
	delete[] d1;
	delete[] d2;
	*/

	delete[] S;
	delete[]S1;


}
