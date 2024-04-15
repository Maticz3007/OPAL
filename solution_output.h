#ifndef SOLUTION_OUTPUT_IS_INCLUDED
#define SOLUTION_OUTPUT_IS_INCLUDED

#include<stdint.h> // uint8_t zajmujacy 1 bajt
#include<stdio.h>
#include "maze_storage.h"  // Pole, Pole_czy_odwiedzone, Pole_skad_doszedl, ...
#include "chunk_manager.h" // zapisz_chunk, wczytaj_chunk_z_Polem, ...

//short int wypisz_liste_krokow(FILE * plik_wejsciowy);
short int wypisz_liste_krokow(FILE * plik_wejsciowy, FILE * plik_wyjsciowy, short int tryb, Pole wejscie, Pole wyjscie);
// tryb - tryb wypisywania:
// 0 - tryb tekstowy                   - wypisuje liste krokow w formacie tekstowym zgodnym z okreslonym w Specyfikacji Funkcjonalnejwypisuje liste krokow w formacie tekstowym zgodnym z okreslonym w Specyfikacji Funkcjonalnej
// 1 - tryb binarny (nowy plik)        - wypisuje liste krokow w formacie binarnym, przy zalozeniu ze plik_wyjsciowy jest uchytem do nowego pliku, ktory wskazuje na jego poczatek
// 2 - tryb binarny (istniejacy plik)  - wypisuje liste krokow w formacie binarnym, przy zalozeniu ze plik_wyjsciowy jest uchytem do wczesniej uzywanego pliku binarnego zawierajacego juz caly labirynt, ktory wskazuje na jego poczatek
// Tryb 0 uzwzglednia Pole startowe i koncowe labiryntu jako czesc sciezki, natomiast
// tryb 1 i 2 nie uwzgledniaja Pola 
// plik_wejsciowy powinien byc otwarty w odpowiednim trybie do czytania, natomiast
// jesli plik_wyjsciowy jest binarny to powinien byc otwarty w trybie do czytania i pisania (rb+), a
// jesli nie jest to w trybie (w) lub moze to byc stdout

// Zwraca dlugosc sciezki od wejscia do wyjscia jezeli ta sciezka istnieje, w przeciwnym wypadku zwraca 0
// Sciezka liczona jest bez Pola startowego do Pola koncowego, dla najmniejszego labiryntu o wymiarach 1x1 wyniesie 1
unsigned int _sprawdz_dlugosc_sciezki(Pole wejscie, Pole wyjscie);

// wypisuje liste krokow w formacie tekstowym zgodnym z okreslonym w Specyfikacji Funkcjonalnej
short int _wypisz_liste_krokow_tekstowo(FILE * plik_wyjsciowy, Pole wejscie, Pole wyjscie);

// Uzywane przy tworzeniu nowych plikow binarnych z rozwiazaniem
// Przepisuje zawartosc oryginalnego pliku do pliku z rozwiazaniem, aby byl zgodny z jego specyfikacja
// konczy przepisywanie, gdy dojdzie do czesci "Sekcja nagłowkowa rozwiazania"
short int _przepisz_plik_do_sekcji_naglowkowej_rozwiazania(FILE * plik_wejsciowy, FILE * plik_wyjsciowy);

// Przechodzi do sekcji naglowkowej rozwiazania, zakladajac ze plik_wyjsciowy
// jest uchytem do wczesniej uzywanego pliku binarnego zawierajacego juz caly labirynt, ktory wskazuje na jego poczatek
short int _przejdz_do_sekcji_naglowkowej_rozwiazania(FILE * plik_wejsciowy);

// uchwyt plik_wyjsciowy powinien wksazywac na czesc "Sekcja nagłowkowa rozwiazania" przed wywolaniem funkcji
// wypisuje cala sekcje rozwiazania do pliku wyjsciowego
short int _wypisz_liste_krokow_binarnie(FILE * plik_wyjsciowy, Pole wejscie, Pole wyjscie);

// Zwraca Pole niebedace czescia ramki labiryntu najblizsze Polu skrajnemu (bedacemu czescia ramki labiryntu)
Pole _zwroc_Pole_przy_skrajnym_Polu(Pole skrajne);

// Zwraca kierunek (uint8_t) jaki nalezy przejsc z Pola P1, aby dostac sie do sasiedniego Pola P2
// 01001110 (znak 'N')  - w gore
// 01000101 (znak 'E')  - w prawo
// 01010011 (znak 'S')  - w dol
// 01010111 (znak 'W')  - w lewo
// 00000000 (znak NULL) - P1 i P2 nie sasiaduja ze soba
uint8_t _kierunek_z_Odcinka(Pole P1, Pole P2);

// Wykorzystuje znak iloczynu wektorowego, aby porownac kierunek1 z kierunek2
// Zwraca:
// 1 - jesli kierunek2 jest na lewo od kierunek1
// 0 - jesli kierunek1 i kierunek 2 sa rownolegle lub jesli podano bezsensowne liczby jako kierunki
// -1 - jesli kierunek2 jest na prawo od kierunek1
short int _wzglednosc_kierunkow(uint8_t kierunek1, uint8_t kierunek2);

#endif // SOLUTION_OUTPUT_IS_INCLUDED