#ifndef MODEL_ISINGA_H
#define MODEL_ISINGA_H

#include "rng.h"

/**
   @author Marek Niewiński <niewinski@linuxHP6715b>
   @author Dominik Kasprowicz
	@version 2.1
   @file
*/
class ModelIsinga 
{
   /**
    * @brief Długość boku kwadratowej siatki.
    */
	const int L;
	int **siatka;	

	/**
	 * @brief Energia wewnętrzna, ktorą osiągnie próbka na końcu eksperymentu.
	 */
	int energia_docelowa_układu;   
	int energia_początkowa_układu;
	
	/**
	 * @brief Energia dostarczana z zewnątrz do próbki – ma sens tylko w układzie mikrokanonicznym.
	 */
	int energia_duszka;
	
	int magnetyzacja;
	float średnia_energia_układu, średnia_energia_duszka, średnia_magnetyzacja, temperatura;
	
	/**
	 * @brief Generator liczb pseudolosowych. Pozwala generować losowe współrzędne \a x i \a y, 
	 * a także losowe liczby rzeczywiste z przedziału [0, 1).
	 */
	RNG generator;

	/**
	 * @brief Ustawia wszystkie spiny "w górę", zamieniając próbkę w pojedynczą domenę magnetyczną.
	 */
	void ustaw_same_jedynki();

	/**
	 * @brief Próbuje odwrócić spin losowo wybranego atomu. 
	 * Sukces tej próby zależy od ustawienia spinów atomów sąsiednich oraz 
	 * od energii przekazanej atomowi przez duszka (układ mikrokanoniczny)
	 * względnie od temperatury próbki (układ kanoniczny).
	 */
	void spróbuj_odwrócić_spin_losowego_atomu();

	/** 
	 * @brief Oblicza zmianę energii wskutek \a hipotetycznego obrócenia spinu 
	 * atomu o podanych współrzędnych (rzeczywisty spin pozostaje bez zmian).
	 * @param x – współrzędna \a x atomu.
	 * @param y – współrzędna \a y atomu.
	 * @return Zmiana energii atomu, która nastąpiłaby wskutek odwrócenia jego spinu.
	 */ 
	int  deltaE(int x, int y);	

public:	
	/** 
	 * @brief Tworzy siatkę kwadratową o zadanej długości boku i energii \a docelowej, 
	 * która zostanie osiągnięta dopiero po przeprowadzeniu eksperymentu, 
	 * tzn. po wywołaniu metod \ref doprowadzenie_do_stanu_równowagi i \ref zliczanie_średnich.
	 * @param rozmiar – długość boku siatki.
	 * @param energia – energia docelowa.
	 */ 	
	ModelIsinga(int rozmiar, int energia);		

	~ModelIsinga();

	/** 
	 * @brief Wybiera losowe atomy próbki i próbuje obrócić ich spiny.
	 * Czynność ta jest powtarzana podaną liczbę razy.
	 * Nie ma gwarancji, że próbka osiągnie równowagę termodynamiczną, 
	 * zwłaszcza przy liczbie kroków mniejszej od liczby atomów w próbce.
	 * @param liczba_kroków – liczba losowań.
	 */ 
	void  doprowadzenie_do_stanu_równowagi(int liczba_kroków);
	
	/** 
	 * @brief Wybiera losowe atomy próbki i próbuje obrócić ich spiny.
	 * Czynność ta jest wykonywana tyle razy, ile atomów liczy próbka, po czym aktualizowane są 
	 * statystyki dotyczące energii duszka i próbki.
	 * Cały ten eksperyment jest powtarzany zadaną liczbę razy, po czym obliczana jest 
	 * uśredniona magnetyzacja, temperatura, energia wewnętrzna próbki i duszka.
	 * @param liczba_kroków – liczba powtórzeń eksperymentu.
	 */ 	
	void  zliczanie_średnich(int liczba_kroków);
	
	float podaj_średnią_energię_duszka();
	float podaj_średnią_energię_układu();
	float podaj_średnią_magnetyzację();
	float podaj_temperaturę();
};

#endif // MODEL_ISINGA_H
