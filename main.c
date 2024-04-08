#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "file_check.h"
#include "RLE_decompressor.h"

char * extension_reader(const char *s)
{
    size_t length = strlen(s);

    return(char*)(length<4 ? s : s+length-4);
}

int main(int argc, char ** argv){
    FILE * plik_wejsciowy = NULL;
    FILE * plik_wyjsciowy = NULL;
    char * m_filepath = NULL;
    char * r_filepath = NULL;
    int c;
    opterr = 0;
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
                             "Unknown option character `\\x%x'.\n",
                             optopt);  //potem przetestuje i dam odpowiednie komentarze
                return 1;
            default:
                abort();
        }
    if(help_flag)
    {
        printf("tutaj będzie jakaś pomoc");
        return -12;
    }

    char ext[5];
    char *extension = extension_reader(r_filepath);
    memcpy(ext, extension, 4);
    printf("%s", ext);


    if(m_filepath != NULL)
    {
        plik_wyjsciowy = fopen(m_filepath, "a");
        sprawdz_dostep_do_zapisu(plik_wyjsciowy);
    }

    if (strcmp(ext, ".bin") == 0)
    {
        RLE_decompression(r_filepath);
        strcpy(r_filepath, "C:\\Users\\Mateusz\\Desktop\\untitled\\maze_test.txt");
    }
    printf("%s\n", r_filepath);
    plik_wejsciowy = fopen(r_filepath, "r");
    sprawdz_dostep_do_odczytu(plik_wejsciowy);
    sprawdz_format_labiryntu(plik_wejsciowy);




}