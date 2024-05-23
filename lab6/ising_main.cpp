#include <iostream>
#include "model_isinga.h"

using namespace std;

/** 
 * @file
 * Główna funkcja programu. 
 * Tworzy model próbki ferromagnetycznej o danej wielkości, wprowadza do niego 
 * zadaną ilość energii (układ mikrokanoniczny) i oblicza statystyki 
 * (temperatura, magnetyzacja itp.)
 * Obecna postać ma charakter czysto demonstracyjny, 
 * ponieważ uwzględnia tylko jedną wielkość siatki i jedną wartość energii docelowej.
 * <b>
 * Przy realizacji zadań z instrukcji należy użyć zagnieżdżonej pętli po wielkościach
 * siatki i energiach docelowych (Zadanie 1 – układ mikrokanoniczny), względnie po
 * wielkościach siatki i temperaturach (Zadanie 2 – układ kanoniczny).
 * </b>
 */
int main(int argc, char *argv[])
{
	cout << "Symulacja modelu Isinga w Zespole Mikrokanonicznym" << endl;
	
	ModelIsinga ising(10, -184);
	ising.doprowadzenie_do_stanu_równowagi(1000);
	ising.zliczanie_średnich(1000);

	cout << "Srednia energia ukladu = " << ising.podaj_średnią_energię_układu() << endl;
	cout << "Srednia energia duszka = " << ising.podaj_średnią_energię_duszka() << endl;
	cout << "Srednia magnetyzacja   = " << ising.podaj_średnią_magnetyzację() << endl;
	cout << "Temperatura            = " << ising.podaj_temperaturę() << endl;
	
	return 0;
}
