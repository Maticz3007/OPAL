#ifndef MAZE_STORAGE_IS_INCLUDED
#define MAZE_STORAGE_IS_INCLUDED

#include<stdint.h> // uint8_t zajmujacy 1 bajt

//#define MAX_MAZE_STORAGE 393217 // okolo, moze wiecej lub mniej aby przechowac caly labirynt na raz
// 393217 * 8 == 3145736 > 3145728 == 1024*1024*3

#define MAX_MAZE_STORAGE 98305 // chunk ma maksymalny rozmiar 512x512
// 98305 * 8 == 786440 > 786432 == 512*512*3

//#define MAX_MAZE_STORAGE 10000
//#define MAX_MAZE_STORAGE 1

typedef struct {
    short int a;
    short int b;
} Pole;

typedef struct {
    short int l_bitow;
    short int l_chunkow; // zgodnie ze specyfikacja l_chunkow^2 to liczba wszystkich chunkow
    short int a;
    short int b;
    short int chunk_a;
    short int chunk_b;
    uint8_t chunk[MAX_MAZE_STORAGE];
    // na potrzeby implementacji:
    short int _l_Pol_w_chunku; // ustawiane przez MazeStorage_inicjuj
} MazeStorage;
// Pierwsze Pole całego labiryntu ma wspolrzedne (1,1), a ostatnie (MazeStorage.a,MazeStorage.b)
// Pierwszy chunk ma wspolrzedne (1,1), a ostatni (MazeStorage.l_chunkow, MazeStorage.l_chunkow)

// Pierwsze Pole wczytanego chunka ma wspolrzedne (1+(MazeStorage.chunk_a-1)*MazeStorage._l_Pol_w_chunku, 1+(MazeStorage.chunk_b-1)*MazeStorage._l_Pol_w_chunku),
// a ostatnie (MazeStorage.chunk_a*MazeStorage._l_Pol_w_chunku, MazeStorage.chunk_b*MazeStorage._l_Pol_w_chunku)

// Pierwsze Pole jest zapisane w MazeStorage.chunk[0] (a nie w 1)

// Pierwszy i drugi bit kazdego Pola to odpowiednio informacje czy mozna isc w prawo i czy mozna isc w dol
// jednoczesnie jest to informacja skad algorytm doszedl do danego Pola (poprzednie jest nadpisywane w momencie odwiedzenia Pola)
// Trzeci bit to czy dane Pole zostalo odwiedzone
// Modul rozwiazujacy moze zdefiniowac uzycie wiecej niz 3 bitow, wlasnie po to jest MazeStorage.l_bitow

extern MazeStorage labirynt; // zdefiniowane w maze_storage.c

short int Pole_czy_istnieje(Pole P);

short int Pole_czy_w_chunku(Pole P);

short int Pole_ustaw_czy_odwiedzone(Pole P, short int czy_odw);

short int Pole_czy_odwiedzone(Pole P);

// Te ponizsze 4 zamiast w module solver_BFS powinny byc tu,
// bo uzywa ich chunkenizer
short int Pole_ustaw_czy_mozna_w_prawo(Pole P);

short int Pole_ustaw_czy_mozna_w_dol(Pole P);

short int Pole_czy_mozna_w_prawo(Pole P); // potrzebne, ale nieokreslone w Specyfikacji Implementacyjnej

short int Pole_czy_mozna_w_dol(Pole P); // potrzebne, ale nieokreslone w Specyfikacji Implementacyjnej

// Ta ostatnia nie moze byc w module solver_BFS,
// bo uzywa jej solution_output
short int Pole_ustaw_skad_doszedl(Pole D, Pole P); // Zamiast Pole PoleD i Pole PoleP

//Pole Pole_skad_doszedl(Pole P);
void Pole_skad_doszedl(Pole * P); // zamiast powyzszego
// informacja o Polu z ktorego algorytm doszedl do P jest zapisywana w P, aby mozna bylo zwrocic NULL
// poza tym nie mozna zwrocic wskaznika na zmienna zadeklarowana lokalnie

// Nie zostało to okreslone w Specyfikacji Implementacyjnej, ale trzeba najpierw zainicjowac MazeStorage
void MazeStorage_inicjuj(short int l_bitow, short int l_chunkow, short int a, short int b, short int chunk_a, short int chunk_b);

void MazeStorage_ustaw_bit(Pole P, short int ktory_bit, short int wartosc);

short int MazeStorage_odczytaj_bit(Pole P, short int ktory_bit);

void MazeStorage_wyczysc();

// ------

// Przeksztalca wspolrzedne Pola P na jego indeks w MazeStorage.chunk
// w odpowiednim dla niego chunku
// Zwraca indeks Pole P jakie ma w MazeStorage.chunk
// Pola o tej samej wzglednej pozycji w roznych chunkach zwroca takie same indeksy
// np. dla labiryntu podzielonego na 2^2 chunki
// (1,1) (2,1) (3,1)|(4,1) (5,1) (6,1)
// (1,2) (2,2) (3,2)|(4,2) (5,2) (6,2)
// (1,3) (2,3) (3,3)|(4,3) (5,3) (6,3)
// -----------------|-----------------
// (1,4) (2,4) (3,4)|(4,4) (5,4) (6,4)
// (1,5) (2,5) (3,5)|(4,5) (5,5) (6,5)
// (1,6) (2,6) (3,6)|(4,6) (5,6) (6,6)
// Pole (5,3) zostanie przeksztalcone na indeks 7, tak samo jak Pole (2,3)
// Funkcja zaklada, ze Pole P istnieje
int _MazeStorage_transformacja_wspolrzednych_Pola(Pole P);

// Przeksztalca pare (numer_Pola, ktory_bit) -> (idx, nb)
// gdzie:
// idx - indeks Pola w MazeStorage.chunk
// nb  - numer bitu dla indeksu idx MazeStorage.chunk, tzn. MazeStorage.chunk[idx][nb] to ktory_bit Pola numer_Pola
// idx zostanie przekazane do numer_Pola, nb do ktory_bit
void _MazeStorage_transformacja_3(int * numer_Pola, short int * ktory_bit);

// DEBUG: wypisuje MazeStorage
// format:
// 1 - podzial na bajty
// 2 - podzial na l_bitow
void _MazeStorage_wypisz(short int format);

#endif // MAZE_STORAGE_IS_INCLUDED