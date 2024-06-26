#include "chunk_manager.h"
#include "maze_storage.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern FILE * pliki_chunkow[MAX_CHUNKI_PIERW+1][MAX_CHUNKI_PIERW+1]; // Zdefiniowane w chunkenizer.c

//gdy zrobimy chunki, wszystkie będą tego samego rozmiaru, 
//3/8 bajta na jedno pole
//powinno być "a_b.chunk"

void wyczysc_chunk() {
    //zaokrąglenie w górę, ustala ilość bajtów w pliku
    double pola = (double)labirynt._l_Pol_w_chunku*labirynt._l_Pol_w_chunku * labirynt.l_bitow / 8;
    int pola_zaokr = (int) ceil(pola);
    char o_filename[MAX_SCIEZKA];
    //char buf[81920]; // -4 kB
    sprintf(o_filename, "%d_%d.chunk", labirynt.chunk_a, labirynt.chunk_b); 
    FILE * chunk = fopen(o_filename, "w");
    //FILE * chunk = pliki_chunkow[labirynt.chunk_a][labirynt.chunk_b];
    //setbuf(chunk, buf);
    char temp = 0;
    for(int i=0; i<pola_zaokr; i++)
    {
        //printf("ZNAK[%d]: %d\n", i, labirynt.chunk[i]);  //<- debugowe
        fwrite(&temp, 1, 1, chunk);
    }
    fclose(chunk); //Jeszcze nie zamykamy
    //rewind(chunk); // Zamiast tego cofamy sie na poczatek
}

short int zapisz_chunk() {
    //printf("Zapisuje chunk (%i, %i).\n", labirynt.chunk_a, labirynt.chunk_b);
     //zaokrąglenie w górę, ustala ilość bajtów w pliku
    double pola = (double)labirynt._l_Pol_w_chunku*labirynt._l_Pol_w_chunku * labirynt.l_bitow / 8;
    int pola_zaokr = (int) ceil(pola);
    char o_filename[MAX_SCIEZKA];
    //char buf[81920]; // -4 kB
    sprintf(o_filename, "%d_%d.chunk", labirynt.chunk_a, labirynt.chunk_b);
    FILE * chunk = fopen(o_filename, "w");
    //FILE * chunk = pliki_chunkow[labirynt.chunk_a][labirynt.chunk_b];
    //setbuf(chunk, buf);
    for(int i=0; i<pola_zaokr; i++)
    {
        fwrite(&labirynt.chunk[i], 1, 1, chunk);
    }
    fclose(chunk); //Jeszcze nie zamykamy
    //rewind(chunk); // Zamiast tego cofamy sie na poczatek
    return 0;
}


short int wczytaj_chunk_o_wspolrzednych(short int a, short int b) {
    //printf("Wczytuje chunk (%i, %i).\n", a, b);
    //zaokrąglenie w górę, ustala ilość bajtów w pliku
    double pola = (double)labirynt._l_Pol_w_chunku*labirynt._l_Pol_w_chunku * labirynt.l_bitow / 8;
    int pola_zaokr = (int) ceil(pola);
    char o_filename[MAX_SCIEZKA];
    //char buf[81920]; // -4 kB
    sprintf(o_filename, "%d_%d.chunk", a, b);
    FILE * chunk = fopen(o_filename, "r");
    //FILE * chunk = pliki_chunkow[labirynt.chunk_a][labirynt.chunk_b];
    if(chunk==NULL) return 50;
    //setbuf(chunk, buf);
    char temp; 
    int i=0;
    // while (fread(&temp, 1, 1, chunk))
    // {                                            //<- ta wersja wczytuje cały plik, niezależnie od jak zainicjowany jest maze_storage
    //     labirynt.chunk[i]=temp;
    //     //printf("ZNAK[%d]: %d\n", i, labirynt.chunk[i]);  //<- debugowe
    //     i++;
    // }
    for(i=0; i<pola_zaokr; i++)
    {
        fread(&temp, 1, 1, chunk);
        labirynt.chunk[i]=temp;
    }
    labirynt.chunk_a = a;labirynt.chunk_b = b;
    fclose(chunk); //Jeszcze nie zamykamy
    //rewind(chunk); // Zamiast tego cofamy sie na poczatek
    //wyczysc_chunk();
    //zapisz_chunk();  
    return 0;
}

short int wczytaj_chunk_z_Polem(Pole P) {
    if(!Pole_czy_istnieje(P)) return 60;
    //zaokrąglenia w górę
    double a_temp = (double)P.a/labirynt._l_Pol_w_chunku ; 
    short int a = (short int) ceil(a_temp);
    double b_temp = (double)P.b/labirynt._l_Pol_w_chunku ;
    short int b = (short int) ceil(b_temp);
    wczytaj_chunk_o_wspolrzednych(a, b);
    // double c_temp = (double)2/3;
    // short int c = (short int) ceil(c_temp);
    // double d_temp = (double)3/3;
    // short int d = (short int) ceil(d_temp);
    // printf("%d,%d", c, d);
    return 0;
}