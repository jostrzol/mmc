#include "model_isinga.h"

ModelIsinga::ModelIsinga(int rozmiar, int energia) 
	: L{rozmiar}
	, energia_docelowa_układu{energia}
	, generator{rozmiar} 
{
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

	if (dE <= energia_duszka) 
	{				
		siatka[i][j] = -siatka[i][j];
		energia_duszka -= dE;
		energia_początkowa_układu  += dE;			
		magnetyzacja += 2*siatka[i][j];
	}
}

void ModelIsinga::doprowadzenie_do_stanu_równowagi(int liczba_kroków) 
{
	magnetyzacja = L * L;
	energia_początkowa_układu  = -2 * L * L;
	energia_duszka = energia_docelowa_układu - energia_początkowa_układu;
	ustaw_same_jedynki();

	for (int k = 0; k < liczba_kroków; ++k) 
	{
		spróbuj_odwrócić_spin_losowego_atomu();
	}
}

// Wyznacza średnią energię duszka, energię wewnętrzną układu, magnetyzację oraz temperaturę
void ModelIsinga::zliczanie_średnich(int liczba_kroków) 
{
	int energia_duszka_do_średniej = 0;
	int energia_układu_do_średniej = 0;	
	int magnetyzacja_tot = 0;
	
	// Pętla liczby_kroków
	for (int k = 0; k < liczba_kroków; ++k) 
	{
		// Pętla statystycznie po każdym spinie
		for (int l = 0; l < L*L; ++l) 
		{
			spróbuj_odwrócić_spin_losowego_atomu();
		}
		energia_duszka_do_średniej += energia_duszka;
		energia_układu_do_średniej += energia_początkowa_układu;
		magnetyzacja_tot += abs(magnetyzacja);
	}

	// Obliczanie średnich
	średnia_energia_duszka = (float)energia_duszka_do_średniej / liczba_kroków;
	średnia_energia_układu = (float)energia_układu_do_średniej / liczba_kroków;
	średnia_magnetyzacja = magnetyzacja_tot / (float)liczba_kroków / ((float)L*(float)L);
	temperatura = 4.0 / (log(1 + 4.0/średnia_energia_duszka));
}

float ModelIsinga::podaj_średnią_energię_duszka() 
{
	return średnia_energia_duszka;
}

float ModelIsinga::podaj_średnią_energię_układu() 
{
	return średnia_energia_układu;
}

float ModelIsinga::podaj_średnią_magnetyzację() 
{
	return średnia_magnetyzacja;
}

float ModelIsinga::podaj_temperaturę() 
{
	return temperatura;
}

