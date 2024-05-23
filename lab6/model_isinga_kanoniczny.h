#ifndef MODEL_ISINGA_KANONICZNY_H
#define MODEL_ISINGA_KANONICZNY_H

#include "model_isinga.h"
#include "rng.h"

/**
   @author Marek Niewiński <niewinski@linuxHP6715b>
   @author Dominik Kasprowicz
	@version 2.1
   @file
*/
class ModelIsingaKanoniczny : public ModelIsinga
{

	/**
	 * @brief Temperatura otoczenia – ma sens tylko w układzie kanonicznym.
	 */
	float temperatura;
	
	float średnia_energia_układu, średnia_magnetyzacja;

	bool czy_odwrócić_spin(float dE);

public:	
	/** 
	 * @brief Tworzy siatkę kwadratową o zadanej długości boku i energii \a docelowej, 
	 * która zostanie osiągnięta dopiero po przeprowadzeniu eksperymentu, 
	 * tzn. po wywołaniu metod \ref doprowadzenie_do_stanu_równowagi i \ref zliczanie_średnich.
	 * @param rozmiar – długość boku siatki.
	 * @param temperatura – temperatura otoczenia.
	 */ 	
	ModelIsingaKanoniczny(int rozmiar, float temperatura);		

	/** 
	 * @brief Wybiera losowe atomy próbki i próbuje obrócić ich spiny.
	 * Czynność ta jest wykonywana tyle razy, ile atomów liczy próbka, po czym aktualizowane są 
	 * statystyki dotyczące energii duszka i próbki.
	 * Cały ten eksperyment jest powtarzany zadaną liczbę razy, po czym obliczana jest 
	 * uśredniona magnetyzacja, temperatura, energia wewnętrzna próbki i duszka.
	 * @param liczba_kroków – liczba powtórzeń eksperymentu.
	 */ 	
	void  zliczanie_średnich(int liczba_kroków);
	
	float podaj_średnią_energię_układu();
	float podaj_średnią_magnetyzację();
	float podaj_temperaturę();
};

#endif // MODEL_ISINGA_H
