//
// Created by Mateusz on 09.04.2024.
//

#ifndef UNTITLED_CHUNKENIZER_H
#define UNTITLED_CHUNKENIZER_H
short int podziel_tekstowy(short int chunki , short int a, short int b, char * plik_wejsciowy);
short int podziel_labirynt(short int l_bitow, short int chunki , short int a, short int b, char * plik_wejsciowy);
short int podglad_bin(short int chunki , short int a, short int b, char * plik_wejsciowy);
void delete_chunks_bin(short int chunki);
void delete_chunks_temp(short int chunki);
#endif //UNTITLED_CHUNKENIZER_H
