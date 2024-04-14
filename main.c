#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "file_check.h"
#include "RLE_decompressor.h"
#include "chunkenizer.h"
#include "chunk_manager.h"
#include "maze_storage.h"

char * extension_reader(const char *s)
{
    size_t length = strlen(s);
    return(char*)(length<4 ? s : s+length-4);
}

int main(int argc, char ** argv){
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
                if(optopt == 'c')
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
                             optopt);  //potem przetestuję i dam odpowiednie komentarze
                return 1;
            default:
                abort();
        }
    if(help_flag)
    {
        printf("tutaj będzie jakaś pomoc");
        return -12;
    }
    char ext[5] = {};
    char *extension = extension_reader(r_filepath);
    memcpy(ext, extension, 4);
    //printf("%s\n", ext);
    if(m_filepath != NULL)
    {
        sprawdz_dostep_do_zapisu(m_filepath);
    }
    if (strcmp(ext, ".bin") == 0)
    {
        RLE_decompression(r_filepath);
        strcpy(r_filepath, "maze_binary_source.txt");
    }
    // printf("%s\n", r_filepath);
    extension = extension_reader(r_filepath);
    memcpy(ext, extension, 4);
    if (strcmp(ext, ".txt") != 0) return -11; //nieprawidłowy plik na wejściu
    error_flag = sprawdz_dostep_do_odczytu(r_filepath);
    if(error_flag==10) return 10; //anty-segfault
    wynik = sprawdz_format_labiryntu(r_filepath);
    delete_chunks_bin(100);
    delete_chunks_temp(100);
    //podglad_bin(1,wynik.szerokosc, wynik.wysokosc,r_filepath);
    podziel_labirynt(1, wynik.szerokosc, wynik.wysokosc,r_filepath);
    //podziel_tekstowy(2, (wynik.szerokosc*2+1), (wynik.wysokosc*2+1), r_filepath);
    MazeStorage_inicjuj(3, 1, 5, 5, 1, 1);
    wczytaj_chunk_o_wspolrzednych(1, 1);
    // for(int i=0; i<98305; i++)
    // printf("%x ", labirynt.chunk[i]);
}
