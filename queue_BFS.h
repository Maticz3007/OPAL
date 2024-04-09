// v2 (otwarcie pliku tylko raz w trybie od odczytu i zapisu, skakanie po nim aby odczytywac i zapisywac w odpowiednich miejscach)
#ifndef QUEUE_BFS_IS_INCLUDED
#define QUEUE_BFS_IS_INCLUDED

#include "maze_storage.h" // Pole
#include "config.h" // TEMP_DIR
#include<stdio.h> // FILE

#define MAX_KOLEJKA 50

//#define KOLEJKA_SCIEZKA TEMP_DIR - uzywajmy po prostu funkcji pomocniczej _kolejka_sciezka_do_pliku oraz sciezki TEMP_DIR
#define KOLEJKA_FORMAT_SCIEZKI_PLIKU "%skolejka%p.queue_BFS" // Trzeba jeszcze dopisac sciezke i (void *)Q dla kolejki Q
//#define KOLEJKA_FORMAT_SCIEZKI_PLIKU "%skolejka.queue_BFS"

typedef struct {
    Pole PoleD;
    Pole PoleP;
} kolejka_element;

typedef struct {
    unsigned short int lel;
    kolejka_element kol[MAX_KOLEJKA];
    unsigned short int poczatek;
    unsigned short int koniec;
    FILE * plik;
    unsigned short int plik_poczatek;
    unsigned short int plik_koniec;
    unsigned short int tryb;
} kolejka;

void kolejka_inicjuj(kolejka * Q);

short int kolejka_zniszcz(kolejka * Q);

//kolejka_element * kolejka_przod(kolejka * Q); - nie da sie zwrocic wskaznika do zmiennej lokalnej przy odczytywaniu z pliku
//short int kolejka_przod(kolejka * Q, kolejka_element * zwrocony_element); - od razu bedziemy zrzucac element przy odczytaniu, bo automatycznie przesuwamy miejsce w pliku

short int kolejka_wrzuc(kolejka * Q, kolejka_element element);

//short int kolejka_zrzuc(kolejka * Q);
short int kolejka_zrzuc(kolejka * Q, kolejka_element * zwrocony_element); // od razu zwracamy zrzucony element

short int _kolejka_przepisz(kolejka * Q);

//

void _kolejka_sciezka_do_pliku(kolejka * Q, char * zwrocona_sciezka);

short int _kolejka_zrob_plik(kolejka * Q);

short int _kolejka_usun_plik(kolejka * Q);

#endif // QUEUE_BFS_IS_INCLUDED