#ifndef UNTITLED_CHUNK_MANAGER_H
#define UNTITLED_CHUNK_MANAGER_H
#include<stdio.h> // FILE
#include "maze_storage.h"

//extern FILE * pliki_chunkow[MAX_CHUNKI_PIERW+1][MAX_CHUNKI_PIERW+1]; // Zdefiniowane w chunkenizer.c

short int wczytaj_chunk_o_wspolrzednych(short int a, short int b);
void wyczysc_chunk();
short int zapisz_chunk();
short int wczytaj_chunk_z_Polem(Pole P);
#endif //UNTITLED_CHUNK_MANAGER_H