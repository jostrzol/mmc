#include "model_isinga_mikrokanoniczny.h"
#include <iostream>

ModelIsingaMikrokanoniczny::ModelIsingaMikrokanoniczny(int rozmiar, int energia)
	: ModelIsinga{rozmiar}, energia_docelowa_układu{energia}
{
	energia_duszka = energia_docelowa_układu - energia_początkowa_układu;
}

bool ModelIsingaMikrokanoniczny::czy_odwrócić_spin(float dE)
{
	if (dE <= energia_duszka) {
		energia_duszka -= dE;
		return true;
	}

	return false;
}

// Wyznacza średnią energię duszka, energię wewnętrzną układu, magnetyzację oraz temperaturę
void ModelIsingaMikrokanoniczny::zliczanie_średnich(int liczba_kroków)
{
	int energia_duszka_do_średniej = 0;
	int energia_układu_do_średniej = 0;
	int magnetyzacja_tot = 0;

	// Pętla liczby_kroków
	for (int k = 0; k < liczba_kroków; ++k)
	{
		// Pętla statystycznie po każdym spinie
		for (int l = 0; l < L * L; ++l)
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
	średnia_magnetyzacja = magnetyzacja_tot / (float)liczba_kroków / ((float)L * (float)L);
	temperatura = 4.0 / (log(1 + 4.0 / średnia_energia_duszka));
}

float ModelIsingaMikrokanoniczny::podaj_średnią_energię_duszka()
{
	return średnia_energia_duszka;
}

float ModelIsingaMikrokanoniczny::podaj_średnią_energię_układu()
{
	return średnia_energia_układu;
}

float ModelIsingaMikrokanoniczny::podaj_średnią_magnetyzację()
{
	return średnia_magnetyzacja;
}

float ModelIsingaMikrokanoniczny::podaj_temperaturę()
{
	return temperatura;
}
