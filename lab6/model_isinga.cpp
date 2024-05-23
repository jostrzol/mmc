#include "model_isinga.h"

ModelIsinga::ModelIsinga(int rozmiar) 
	: L{rozmiar}
	, generator{rozmiar} 
{
	magnetyzacja = L * L;
	energia_początkowa_układu  = -2 * L * L;
	siatka = new int* [L];
	for (int i = 0; i < L; i++)
		siatka[i] = new int[L];
}	

ModelIsinga::~ModelIsinga() 
{
	if (siatka)
	{
        for (int i = 0; i < L; i++)
            delete[] siatka[i];
        delete[] siatka;
	}
}

void ModelIsinga::ustaw_same_jedynki() 
{
	for(int i = 0; i < L; i++)
		for(int j = 0; j < L; j++)
			siatka[i][j] = 1;
}

int ModelIsinga::deltaE(int x, int y) 
{
	// Periodyczne warunki brzegowe.
	int górny = (x != 0)   ? x-1 : L-1;
	int dolny = (x != L-1) ? x+1 : 0;
	int prawy = (y != L-1) ? y+1 : 0;
	int lewy  = (y != 0)   ? y-1 : L-1;

	int E_pocz = siatka[x][y] * ( siatka[x][lewy] + siatka[x][prawy] + siatka[górny][y] + siatka[dolny][y] );
	int E_końc = -E_pocz;

	return E_pocz - E_końc;
}

void ModelIsinga::spróbuj_odwrócić_spin_losowego_atomu() 
{
	int i = generator.losuj_współrzedną();
	int j = generator.losuj_współrzedną();
	int dE = deltaE(i, j);

	if (czy_odwrócić_spin(dE)) 
	{				
		siatka[i][j] = -siatka[i][j];
		energia_początkowa_układu  += dE;			
		magnetyzacja += 2*siatka[i][j];
	}
}

void ModelIsinga::doprowadzenie_do_stanu_równowagi(int liczba_kroków) 
{
	ustaw_same_jedynki();

	for (int k = 0; k < liczba_kroków; ++k) 
	{
		spróbuj_odwrócić_spin_losowego_atomu();
	}
}

