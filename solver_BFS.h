#ifndef SOLVER_BFS_IS_INCLUDED
#define SOLVER_BFS_IS_INCLUDED

#include "maze_storage.h"  // Pole, Pole_ustaw_czy_odwiedzone, Pole_czy_odwiedzone, Pole_ustaw_skad_doszedl, Pole_czy_mozna_w_prawo, Pole_czy_mozna_w_dol, ...
#include "chunk_manager.h" // zapisz_chunk, wczytaj_chunk_z_Polem, ...
#include "chunkenizer.h"   // podziel_labirynt
#include "queue_BFS.h"     // Kolejka_inicjuj, Kolejka_wrzuc, Kolejka_zrzuc, ...

//short int rozwiaz_BFS(Pole przy_wejsciu, Pole przy_wyjsciu); - musimy znac wymiary labiryntu i plik, w ktorym jest przechowywany, aby go podzielic i zainicjowac MazeStorage
short int rozwiaz_BFS(Pole przy_wejsciu, Pole przy_wyjsciu, short int a, short int b, char * plik_wejsciowy);
// a - liczba kolumn labiryntu, b - liczba wierszy labiryntu, plik_wejsciowy - plik do podzialu na chunki

//short int Pole_ustaw_czy_mozna_w_prawo(Pole P); - przeniesione do modulu maze_storage

//short int Pole_ustaw_czy_mozna_w_dol(Pole P); - przeniesione do modulu maze_storage

#endif // SOLVER_BFS_IS_INCLUDED