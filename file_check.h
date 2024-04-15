//
// Created by Mateusz on 04.04.2024.
//
typedef struct {
    short int szerokosc;
    short int wysokosc;
    short int x_poczatek;
    short int y_poczatek;
    short int x_koniec;
    short int y_koniec;
    short int kod_bledu;
} WynikLabiryntu;
#ifndef UNTITLED_FILE_CHECK_H
#define UNTITLED_FILE_CHECK_H
short int sprawdz_dostep_do_odczytu(char * plik_wejsciowy);
short int sprawdz_dostep_do_zapisu(char * plik_wejsciowy);
WynikLabiryntu sprawdz_format_labiryntu(char * plik_wejsciowy);
#endif //UNTITLED_FILE_CHECK_H
