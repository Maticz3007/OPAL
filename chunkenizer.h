//
// Created by Mateusz on 09.04.2024.
//

#ifndef UNTITLED_CHUNKENIZER_H
#define UNTITLED_CHUNKENIZER_H
short int podziel_tekstowy(short int chunki , short int a, short int b, char * plik_wejsciowy);
short int podziel_labirynt(short int chunki , short int a, short int b, char * plik_wejsciowy);
short int podglad_bin(short int chunki , short int a, short int b, char * plik_wejsciowy);
void delete_chunks(short int chunki, char * file_name, char * extension);
#endif //UNTITLED_CHUNKENIZER_H
