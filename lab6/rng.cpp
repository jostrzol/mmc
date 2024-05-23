#include "rng.h"

RNG::RNG(int bok_siatki) 
	: źródło_losowe{26052023}
	, rozkład_lokalizacji{0, bok_siatki-1}
	, rozkład_jednostajny_0_1{0, 1}
{ }

int RNG::losuj_współrzedną()   { return rozkład_lokalizacji(źródło_losowe); }

float RNG::losuj_z_zakresu_0_1() { return rozkład_jednostajny_0_1(źródło_losowe); }
