#ifndef MODEL_ISINGA_MIKROKANONICZNY_H
#define MODEL_ISINGA_MIKROKANONICZNY_H

#include "model_isinga.h"

/**
   @author Marek Niewiński <niewinski@linuxHP6715b>
   @author Dominik Kasprowicz
	@version 2.1
   @file
*/
class ModelIsingaMikrokanoniczny : public ModelIsinga
{
	/**
	 * @brief Energia dostarczana z zewnątrz do próbki – ma sens tylko w układzie mikrokanonicznym.
	 */
	int energia_duszka;

	int energia_docelowa_układu;
	
	float średnia_energia_układu, średnia_energia_duszka, średnia_magnetyzacja, temperatura;
	
	bool czy_odwrócić_spin(float dE);

public:	
	/** 
	 * @brief Tworzy siatkę kwadratową o zadanej długości boku i energii \a docelowej, 
	 * która zostanie osiągnięta dopiero po przeprowadzeniu eksperymentu, 
	 * tzn. po wywołaniu metod \ref doprowadzenie_do_stanu_równowagi i \ref zliczanie_średnich.
	 * @param rozmiar – długość boku siatki.
	 * @param energia – energia docelowa.
	 */ 	
	ModelIsingaMikrokanoniczny(int rozmiar, int energia);		
	
	/** 
	 * @brief Wybiera losowe atomy próbki i próbuje obrócić ich spiny.
	 * Czynność ta jest wykonywana tyle razy, ile atomów liczy próbka, po czym aktualizowane są 
	 * statystyki dotyczące energii duszka i próbki.
	 * Cały ten eksperyment jest powtarzany zadaną liczbę razy, po czym obliczana jest 
	 * uśredniona magnetyzacja, temperatura, energia wewnętrzna próbki i duszka.
	 * @param liczba_kroków – liczba powtórzeń eksperymentu.
	 */ 	
	void zliczanie_średnich(int liczba_kroków);
	
	float podaj_średnią_energię_duszka();
	float podaj_średnią_energię_układu();
	float podaj_średnią_magnetyzację();
	float podaj_temperaturę();
};

#endif // MODEL_ISINGA_H
