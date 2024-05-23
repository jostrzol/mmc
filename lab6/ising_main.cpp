#include <iostream>
#include "model_isinga.h"
#include "model_isinga_mikrokanoniczny.h"

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
    int bok_mapy = 10;
    int energia = -184;
    bool energia_ustawiona = false;
    int temperatura = 0;
    bool temperatura_ustawiona = false;
    double liczba_krokow = 1000;

    int i = 1;
    while (i < argc)
    {
        const std::string name = argv[i++];
        if (i >= argc)
        {
            std::cerr << "argument '" << name << "' nie ma wartości\n";
            return 1;
        }
        const std::string value_str = argv[i++];

        if (name == "--bok-mapy")
        {
            bok_mapy = std::stoi(value_str);
        }
        else if (name == "--energia")
        {
            energia = std::stoi(value_str);
            energia_ustawiona = true;
        }
        else if (name == "--temperatura")
        {
            temperatura = std::stod(value_str);
            temperatura_ustawiona = true;
        }
        else if (name == "--liczba-krokow")
        {
            liczba_krokow = std::stoi(value_str);
        }
        else
        {
            std::cerr << "nieznany argument '" << name << "'\n";
            return 1;
        }

        if (temperatura_ustawiona && energia_ustawiona)
        {
            std::cerr << "nie można jednocześnie ustawić energii (model mikrokanoniczny) "
                      << "i temperatury (model kanoniczny)" << "'\n";
            return 1;
        }
    }

    if (!temperatura_ustawiona)
        cout << "Symulacja modelu Isinga w Zespole Mikrokanonicznym" << endl;
    else
        cout << "Symulacja modelu Isinga w Zespole Kanonicznym" << endl;

    ModelIsingaMikrokanoniczny ising(bok_mapy, energia);
    ising.doprowadzenie_do_stanu_równowagi(liczba_krokow);
    ising.zliczanie_średnich(liczba_krokow);

    cout << "Srednia energia ukladu = " << ising.podaj_średnią_energię_układu() << endl;
    cout << "Srednia energia duszka = " << ising.podaj_średnią_energię_duszka() << endl;
    cout << "Srednia magnetyzacja   = " << ising.podaj_średnią_magnetyzację() << endl;
    cout << "Temperatura            = " << ising.podaj_temperaturę() << endl;

    return 0;
}
