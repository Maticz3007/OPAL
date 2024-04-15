//
// Created by Mateusz on 04.04.2024.
//
#include <stdio.h>
#include "file_check.h"




short int sprawdz_dostep_do_odczytu(char * plik_wejsciowy)
{
    FILE * maze_input = fopen(plik_wejsciowy, "r");
    if(maze_input==NULL) return 10;
    fclose(maze_input);
    return 0;

}

short int sprawdz_dostep_do_zapisu(char * plik_wyjsciowy)
{
    FILE * maze_output = fopen(plik_wyjsciowy, "r");
    if(maze_output==NULL) return 20;
    fclose(maze_output);
    return 0;
}

//implementacja w obecnej formie zwraca ostatni napotkany błąd
//do poprawienia ale potem

WynikLabiryntu sprawdz_format_labiryntu(char * plik_wejsciowy)
{
    FILE * maze_input = fopen(plik_wejsciowy, "r");
    WynikLabiryntu wynik;
    short int wejscia = 0;
    short int wyjscia = 0;
    short int obecny_x = 0;
    short int obecny_y = 1;
    wynik.szerokosc = 0;
    wynik.wysokosc = 0;
    wynik.x_poczatek = 0;
    wynik.y_poczatek = 0;
    wynik.x_koniec = 0;
    wynik.y_koniec = 0;
    wynik.kod_bledu = 0;
    char bottom_row_check = 0;
    char znak;
    while((znak = fgetc(maze_input)) != EOF)
    {
        if(obecny_x==0) bottom_row_check=0;
        obecny_x++;
        switch(znak)
        {
            case 'P':
                wejscia++;
                if(wejscia > 1) wynik.kod_bledu=31;
                wynik.x_poczatek = obecny_x;
                wynik.y_poczatek = obecny_y;
                break;

            case 'K':
                wyjscia++;
                if(wyjscia > 1) wynik.kod_bledu=33;
                wynik.x_koniec = obecny_x;
                wynik.y_koniec = obecny_y;
                break;
            case 'X':
                break;
            case ' ':
                if(obecny_x==1 || obecny_x==wynik.szerokosc-1 || obecny_y==1)
                    wynik.kod_bledu=39;
                bottom_row_check++;
                break;
            case '\n':
                if(obecny_y==1) wynik.szerokosc = obecny_x;
                else if(obecny_x!=wynik.szerokosc) wynik.kod_bledu=37;
                obecny_x=0;
                obecny_y++;
                break;
            default:
                wynik.kod_bledu=36;
        }

    }
    if(wejscia==0) wynik.kod_bledu= 30;
    if(wyjscia==0) wynik.kod_bledu= 32;
    if(bottom_row_check) wynik.kod_bledu= 39;
    wynik.szerokosc--;
    wynik.wysokosc=obecny_y-1;
    //potwornie ten if wygląda
    if((wynik.x_poczatek!=1 && wynik.x_poczatek!=wynik.szerokosc && wynik.y_poczatek!=1 && wynik.y_poczatek!=wynik.szerokosc) ||
       ((wynik.x_poczatek==1 || wynik.x_poczatek==wynik.szerokosc) && (wynik.y_poczatek==1 || wynik.y_poczatek==wynik.wysokosc ))) wynik.kod_bledu=34;
    if((wynik.x_koniec!=1 && wynik.x_koniec!=wynik.szerokosc && wynik.y_koniec!=1 && wynik.y_koniec!=wynik.szerokosc) ||
        ((wynik.x_koniec==1 || wynik.x_koniec==wynik.szerokosc) && (wynik.y_koniec==1 || wynik.y_koniec==wynik.wysokosc ))) wynik.kod_bledu= 35;
    printf("P: %d, %d\n", wynik.x_poczatek, wynik.y_poczatek); //kolumna, wiersz
    printf("K: %d, %d\n", wynik.x_koniec, wynik.y_koniec);
    printf("Rozmiary pliku: %d, %d\n", wynik.szerokosc, wynik.wysokosc);
    fclose(maze_input);
    wynik.szerokosc/=2;
    wynik.wysokosc/=2;
    return wynik;
}
