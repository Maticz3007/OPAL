//
// Created by Mateusz on 04.04.2024.
//
#include <stdio.h>
#include "file_check.h"


short int sprawdz_dostep_do_odczytu(FILE * maze_input)
{
    if(maze_input==NULL) return 10;
    else return 0;
}

short int sprawdz_dostep_do_zapisu(FILE * maze_output)
{
    if(maze_output==NULL) return 20;
    else return 0;
}


short int sprawdz_format_labiryntu(FILE * maze_input)
{
    short int wejscia = 0;
    short int wyjscia = 0;
    short int obecny_x = 0;
    short int obecny_y = 1;
    short int szerokosc = 0;
    short int wysokosc;
    char znak;
    short int x_poczatek;
    short int y_poczatek;
    short int x_koniec;
    short int y_koniec;
    char bottom_row_check = 0;

    while((znak = fgetc(maze_input)) != EOF)
    {
        if(obecny_x==0) bottom_row_check=0;
        obecny_x++;
        switch(znak)
        {
            case 'P':
                wejscia++;
                if(wejscia > 1) return 31;
                x_poczatek = obecny_x;
                y_poczatek = obecny_y;
                break;

            case 'K':
                wyjscia++;
                if(wyjscia > 1) return 33;
                x_koniec = obecny_x;
                y_koniec = obecny_y;
                break;
            case 'X':
                break;
            case ' ':
                if(obecny_x==1 || obecny_x==szerokosc-1 || obecny_y==1)
                    return 39;
                bottom_row_check++;
                break;
            case '\n':
                if(obecny_y==1) szerokosc = obecny_x;
                else if(obecny_x!=szerokosc) return 37;
                obecny_x=0;
                obecny_y++;
                break;
            default:
                return 36;
        }

    }
    if(wejscia==0) return 30;
    if(wyjscia==0) return 32;
    if(bottom_row_check) return 39;
    szerokosc--;
    wysokosc=obecny_y-1;
    if((x_poczatek!=1 && x_poczatek!=szerokosc && y_poczatek!=1 && y_poczatek!=szerokosc) ||
       ((x_poczatek==1 || x_poczatek==szerokosc) && (y_poczatek==1 || y_poczatek==wysokosc ))) return 34;
    if((x_koniec!=1 && x_koniec!=szerokosc && y_koniec!=1 && y_koniec!=szerokosc) ||
        ((x_koniec==1 || x_koniec==szerokosc) && (y_koniec==1 || y_koniec==wysokosc ))) return 35;
    printf("P: %d, %d\n", x_poczatek, y_poczatek); //kolumna, wiersz
    printf("K: %d, %d\n", x_koniec, y_koniec);
    printf("Rozmiary pliku: %d, %d\n", szerokosc, wysokosc);
    return 0;
}
