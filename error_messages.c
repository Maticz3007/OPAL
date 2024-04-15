#include "error_messages.h"
#include <stdio.h>
#include <stdlib.h>
void podaj_komunikat_bledu(short int kod_bledu)
{
    switch (kod_bledu)
    {
        case -10:
        fprintf(stderr, "W celu zapoznania się z działaniem programu, uruchom go z argumentem -h");
        printf(":huh");
        break;
        case -11:
        fprintf(stderr, "Podano nieprawidłowe argumenty. W celu zapoznania się z działaniem programu, uruchom go z argumentem -h");
        break;
        // case -12:
        // printf("pomoc tutaj"); //wypisz_pomoc()
        // break;
        case 10:
        fprintf(stderr, "Nie można odnaleźć pliku o podanej nazwie.");
        break;
        case 11:
        fprintf(stderr, "Brak dostępu do pliku o podanej nazwie.");
        break; //20, 21 do zrobienia
        case 30:
        fprintf(stderr, "Labirynt nie ma wejścia.");
        break;
        case 31:
        fprintf(stderr, "Labirynt ma wiele wejść.");
        break;
        case 32:
        fprintf(stderr, "Labirynt nie ma wyjścia.");
        break;
        case 33:
        fprintf(stderr, "Labirynt ma wiele wyjść.");
        break;
        case 34:
        fprintf(stderr, "Wejście jest w nieprawidłowym miejscu.");
        break;
        case 35:
        fprintf(stderr, "Wyjście jest w nieprawidłowym miejscu.");
        break;
        case 36:
        fprintf(stderr, "Niedozwolony znak w pliku z labiryntem.");
        break;
        case 37:
        fprintf(stderr, "Wiersz jest różnej długości względem pierwszego.");
        break;
        case 39:
        fprintf(stderr, "Dziury w zewnętrznej ścianie labiryntu.");
        break;
        case -20:
        fprintf(stderr, "NIepowodzenie utworzenia tymczasowego pliku.");
        break;       
        case -100:  
        fprintf(stderr, "Niepoprawny separator w pliku binarnym.");
        break;  
        case -101:
        fprintf(stderr, "Pole labiryntu nie jest oznaczone prawidłowym znakiem.");
        break;  
        case -30:
        fprintf(stderr, "Nie wczytano chunka z Polem.");
        break;
        case -31:
        fprintf(stderr, "Wskazane Pole nie istnieje.");
        break;
        case -32:
        fprintf(stderr, "Pole było już odwiedzone.");
        break;
        case -40:
        fprintf(stderr, "Nie wczytano chunka z Polem.");
        break;
        case -41:
        fprintf(stderr, "Wskazane Pole nie istnieje.");
        break;
        case -42:
        fprintf(stderr, "Pole było już odwiedzone.");
        break;
        case 40:
        fprintf(stderr, "Zapis chunku nie powiódł się.");
        break;
        case 50:
        fprintf(stderr, "Pole w wskazanym chunku nie istnieje.");
        break;
        case 51:
        fprintf(stderr, "Wczytanie chunka nie powiodło się.");
        break;
        case 60:
        fprintf(stderr, "Pole P nie istnieje.");
        break;
        case 61:
        fprintf(stderr, "Wczytanie chunka nie powiodło się.");
        break;
        case -50:
        fprintf(stderr, "Nie wczytano chunka z Polem.");
        break;
        case -60:
        fprintf(stderr, "Pole w wskazanym chunku nie istnieje.");
        break;
        case -61:
        fprintf(stderr, "Pole nie istnieje lub Pole nie sąsiaduje z Polem, z którego się doszło.");
        break;
        case -70:
        fprintf(stderr, "Nie wczytano chunka z Polem.");
        break;
        case -71:
        fprintf(stderr, "Pole P nie istnieje");
        break;
        case 70:
        fprintf(stderr, "Brak dostępu do kolejki, lub przepisanie do pliku nie powiodło się.");
        break;
        case 0:
        break;
        default:
        fprintf(stderr, "Wystąpił błąd: %d", kod_bledu);
        // case :
        // fprintf(stderr, );
        // break;
    }
    if(kod_bledu!=0) exit(kod_bledu);
}