#include "model_isinga_kanoniczny.h"
#include <iostream>

ModelIsingaKanoniczny::ModelIsingaKanoniczny(int rozmiar, float temperatura)
	: ModelIsinga{rozmiar}, temperatura{temperatura}
{
}

bool ModelIsingaKanoniczny::czy_odwrócić_spin(float dE)
{
	auto prawdopodobieństwo_odwrócenia = exp(-dE / temperatura);
	auto losowa_liczba = generator.losuj_z_zakresu_0_1();
	return losowa_liczba <= prawdopodobieństwo_odwrócenia;
}

// Wyznacza średnią energię wewnętrzną układu oraz magnetyzację
void ModelIsingaKanoniczny::zliczanie_średnich(int liczba_kroków)
{
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
		energia_układu_do_średniej += energia_początkowa_układu;
		magnetyzacja_tot += abs(magnetyzacja);
	}

	// Obliczanie średnich
	średnia_energia_układu = (float)energia_układu_do_średniej / liczba_kroków;
	średnia_magnetyzacja = magnetyzacja_tot / (float)liczba_kroków / ((float)L * (float)L);
}

float ModelIsingaKanoniczny::podaj_średnią_energię_układu()
{
	return średnia_energia_układu;
}

float ModelIsingaKanoniczny::podaj_średnią_magnetyzację()
{
	return średnia_magnetyzacja;
}

float ModelIsingaKanoniczny::podaj_temperaturę()
{
	return temperatura;
}
