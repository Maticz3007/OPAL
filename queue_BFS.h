// v2 (otwarcie pliku tylko raz w trybie od odczytu i zapisu, skakanie po nim aby odczytywac i zapisywac w odpowiednich miejscach)
#ifndef QUEUE_BFS_IS_INCLUDED
#define QUEUE_BFS_IS_INCLUDED

#include "maze_storage.h" // Pole
#include "config.h" // TEMP_DIR
#include<stdio.h> // FILE

#define MAX_KOLEJKA 50

//#define KOLEJKA_SCIEZKA TEMP_DIR - uzywajmy po prostu funkcji pomocniczej _Kolejka_sciezka_do_pliku oraz sciezki TEMP_DIR
#define KOLEJKA_FORMAT_SCIEZKI_PLIKU "%sKolejka%p.queue_BFS" // Trzeba jeszcze dopisac sciezke i (void *)Q dla kolejki Q
//#define KOLEJKA_FORMAT_SCIEZKI_PLIKU "%sKolejka.queue_BFS"

typedef struct {
    Pole PoleD;
    Pole PoleP;
} KolejkaElement;

typedef struct {
    unsigned short int lel;
    KolejkaElement kol[MAX_KOLEJKA];
    unsigned short int poczatek;
    unsigned short int koniec;
    FILE * plik;
    unsigned short int plik_poczatek;
    unsigned short int plik_koniec;
    unsigned short int tryb;
} Kolejka;

void Kolejka_inicjuj(Kolejka * Q);

short int Kolejka_zniszcz(Kolejka * Q);

//KolejkaElement * Kolejka_przod(Kolejka * Q); - nie da sie zwrocic wskaznika do zmiennej lokalnej przy odczytywaniu z pliku
//short int Kolejka_przod(Kolejka * Q, KolejkaElement * zwrocony_element); - od razu bedziemy zrzucac element przy odczytaniu, bo automatycznie przesuwamy miejsce w pliku

short int Kolejka_wrzuc(Kolejka * Q, KolejkaElement element);

//short int Kolejka_zrzuc(Kolejka * Q);
short int Kolejka_zrzuc(Kolejka * Q, KolejkaElement * zwrocony_element); // od razu zwracamy zrzucony element

short int _Kolejka_przepisz(Kolejka * Q);

//

void _Kolejka_sciezka_do_pliku(Kolejka * Q, char * zwrocona_sciezka);

short int _Kolejka_zrob_plik(Kolejka * Q);

short int _Kolejka_usun_plik(Kolejka * Q);

#endif // QUEUE_BFS_IS_INCLUDED