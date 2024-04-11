#include "maze_storage.h"
#include<stdio.h> // NULL

int main(int argc, char ** argv) {
    MazeStorage_inicjuj(3,1,7,7,1,1);
    //MazeStorage_inicjuj(3,1,1024,1024,1,1);
    //MazeStorage_inicjuj(3,1,10,10,1,1);
    //MazeStorage_inicjuj(3,1,1,1,1,1);
    Pole P;
    // Ustawianie wszystkiego na 1
    /*short int a,b,ktory_bit;
    for (b = 1;b <= labirynt.b;b++) {
        P.b = b;
        for (a = 1;a <= labirynt.a;a++) {
            P.a = a;
            for (ktory_bit = 1;ktory_bit <= labirynt.l_bitow;ktory_bit++) {
                MazeStorage_ustaw_bit(P,ktory_bit,1);
            }
        }
    }*/
    P.a = 1;P.b = 1;
    Pole_ustaw_czy_mozna_w_prawo(P);
    P.a = 2;P.b = 1;
    Pole_ustaw_czy_mozna_w_dol(P);
    P.a = 3;P.b = 1;
    Pole_ustaw_czy_odwiedzone(P,1);

    /*MazeStorage_ustaw_bit(P,1,1);
    MazeStorage_ustaw_bit(P,2,1);
    MazeStorage_ustaw_bit(P,3,1);*/
    
    _MazeStorage_wypisz(1);
    _MazeStorage_wypisz(2);
}