//
// Created by Mateusz on 09.04.2024.
//

#ifndef UNTITLED_CHUNKENIZER_H
#define UNTITLED_CHUNKENIZER_H
#include "config.h"
#include <stdio.h>

//extern FILE * pliki_chunkow[MAX_CHUNKI_PIERW+1][MAX_CHUNKI_PIERW+1]; // Zdefiniowane w chunkenizer.c

short int podziel_tekstowy(short int chunki , short int a, short int b, char * plik_wejsciowy);
short int podziel_labirynt(short int l_bitow, short int chunki , short int a, short int b, FILE * maze_input);
short int podglad_bin(short int chunki , short int a, short int b, char * plik_wejsciowy);
void delete_chunks_bin(short int chunki);
void delete_chunks_temp(short int chunki);

void _zamknij_pliki_chunkow(short int chunki);
#endif //UNTITLED_CHUNKENIZER_H
