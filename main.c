#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "error_messages.h"
#include "file_check.h"
#include "RLE_decompressor.h"
#include "maze_storage.h"
#include "solver_BFS.h"

char * extension_reader(const char *s)
{
    size_t length = strlen(s);
    return(char*)(length<4 ? s : s+length-4);
}

int main(int argc, char ** argv) {
    WynikLabiryntu wynik;
    char * m_filepath = NULL;
    char * r_filepath = NULL;
    int c;
    opterr = 0;
    short int error_flag=0;
    short int help_flag=0;
    while((c = getopt(argc, argv, "hm:r:")) != -1)
        switch (c)
        {
            case 'h':
                help_flag = 1;
                break;
            case 'm':
                m_filepath = optarg;
                break;
            case 'r':
                r_filepath = optarg;
                break;
            case '?':
                if(optopt == 'r' || optopt == 'm')
                    fprintf (stderr, "Opcja -%c wymaga argumentu.\n", optopt);
                else if (isprint (optopt))
                {
                    fprintf(stderr,
                            "Podano nieprawidłowe argumenty. W celu zapoznania się z działaniem programu, uruchom go z argumentem -h `-%c'.\n",
                            optopt);
                    return -11;
                }
                else
                    fprintf (stderr,
                             "Nieprawidłowy argument.`\\x%x'.\n",
                             optopt); 
                return 1;
            default:
                podaj_komunikat_bledu(-10);
        }
    if(help_flag)
    {
        printf("tutaj będzie jakaś pomoc");
        return -12;
    }
    //if(r_filepath==NULL) podaj_komunikat_bledu(-10);
    char ext[5] = {0,0,0,0,0};
    char *extension = extension_reader(r_filepath);
    memcpy(ext, extension, 4);
    if(m_filepath != NULL)
    {
        error_flag=sprawdz_dostep_do_zapisu(m_filepath);
    }
    podaj_komunikat_bledu(error_flag);
    if (strcmp(ext, ".bin") == 0)
    {
        error_flag=RLE_decompression(r_filepath);
        podaj_komunikat_bledu(error_flag);
        strcpy(r_filepath, "maze_binary_source.txt");
    }
    extension = extension_reader(r_filepath);
    memcpy(ext, extension, 4);
    if (strcmp(ext, ".txt") != 0) podaj_komunikat_bledu(-11);
    error_flag = sprawdz_dostep_do_odczytu(r_filepath);
    podaj_komunikat_bledu(error_flag);
    wynik = sprawdz_format_labiryntu(r_filepath);
    FILE * maze_input = fopen(r_filepath, "r");
    //delete_chunks_bin(5);
    //delete_chunks_temp(5);
    Pole wej;
    Pole wyj;
    wej.a=wynik.x_poczatek;
    wej.b=wynik.y_poczatek;
    wyj.a=wynik.x_koniec;
    wyj.b=wynik.y_koniec;

    error_flag = rozwiaz_BFS(wej, wyj, wynik.szerokosc, wynik.wysokosc, maze_input);
    podaj_komunikat_bledu(error_flag);

    //można niby dać podaj_komunikat_bledu(rozwiaz_BFS(wej, wyj, wynik.szerokosc, wynik.wysokosc, maze_input));
    
    //int jajo = rozwiaz_BFS(wej, wyj, 5, 5, maze_input);
    //rozwiaz_BFS(Pole przy_wejsciu, Pole przy_wyjsciu, short a, short b, char *plik_wejsciowy)
    _MazeStorage_wypisz(2);
    fclose(maze_input);
    //_zamknij_pliki_chunkow(1);
    //MazeStorage_inicjuj(3, 1, 5, 5, 1, 1);
    //podglad_bin(1,wynik.szerokosc, wynik.wysokosc,r_filepath);
    //podziel_labirynt(labirynt.l_bitow, 1, wynik.szerokosc, wynik.wysokosc,r_filepath);
    //podziel_tekstowy(2, (wynik.szerokosc*2+1), (wynik.wysokosc*2+1), r_filepath);
    //wczytaj_chunk_o_wspolrzednych(1, 1);
    // for(int i=0; i<98305; i++)
    // printf("%x ", labirynt.chunk[i]);
    //printf("%d\n", jajo);
    remove("maze_binary_source.txt");
}