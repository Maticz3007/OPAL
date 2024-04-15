//
// Created by Mateusz on 09.04.2024.
//
#include <stdio.h>
#include "chunkenizer.h"
//zasada działania: dzieli plik na chunki w formacie zbliżonym do przez CIebie podanego (bez spacji/newline) do plików tekstowych, 
//następnie na podstawie danych z nich robi pliki binarne
//wychodzi z tego tona malloca tylko i wyłącznie bo otwieranie/zamykanie plików z niego korzysta
//a jednak nie! ponieważ fwrite
//usun_chunki (delete_chunks ale nazwę zmienimy potem) może wybrać co kasuje -> docelowo usuniemy .txt po utworzeniu .bin, a .bin jak program się skończy
short int podziel_labirynt(short int l_bitow, short int chunki , short int a, short int b, FILE * maze_input)
{
    //FILE * maze_input = fopen(plik_wejsciowy, "r");
    FILE * pliki[chunki];
    FILE * input;
    FILE * output;
    char temp;
    int x_counter = 0;
    int y_counter = 1;
    int lines_in_chunk = 0;
    int first_line_skip = 1;
    int split_counter = 0;
    short int rozmiar_chunka;
    int buffer_size = 2*a;
    int buffer_amount=0;
    char buffer[buffer_size];
    int current_stream=0;
    int file_counter=0;
    char t_filename[100];
    int index=0;
    int output_value=0;
    char o_filename[100];
    //char buf[chunki+1][81920]={}; //bez tablicy 2D zapis się mocno psuł
    //setbuf(maze_input, buf[0]);
    if(a<b)
    {
        rozmiar_chunka = b/chunki;
        if(chunki*rozmiar_chunka!=b) rozmiar_chunka++;
    }
    else
    {
        rozmiar_chunka = a/chunki;
        if(chunki*rozmiar_chunka!=a) rozmiar_chunka++;
    }

    for(int i=0; i<chunki; i++)
    {
        sprintf(t_filename, "%s_%d_%d.txt", "temp", i+1, 1);
        pliki[i] = fopen(t_filename, "w");
        //setbuf(pliki[i], buf[i]);
    }
    while((temp = fgetc(maze_input)) != EOF)
    {
        x_counter++;
        if(temp=='\n')
        {
            y_counter++;
            x_counter=0;
            first_line_skip=0;
        }
        else
        {
            if(!first_line_skip)
            {
                if(((x_counter+y_counter)%2==1 && x_counter!=1))
                {
                    //fprintf(maze_output, "%c", temp);
                    buffer[buffer_amount]=temp;
                    buffer_amount++;
                    if(buffer_amount==buffer_size)
                    {
                        buffer_amount=0;
                        for(int i=0; i<a; i++)
                        {
                            if(split_counter==rozmiar_chunka)
                            {
                                current_stream++;
                                split_counter=0;
                            }
                            if(buffer[i] == ' ') fprintf(pliki[current_stream], "%c", '1');
                            else fprintf(pliki[current_stream], "%c", '0');
                            if(buffer[i+a] == ' ') fprintf(pliki[current_stream], "%c", '1');
                            else fprintf(pliki[current_stream], "%c", '0');
                            fprintf(pliki[current_stream], "%c", '0'); //tutaj można dać pętlę for jeśli potrzebne będzie więcej niż 3 bity na pole
                            //fprintf(pliki[current_stream], "%c", ' ');
                            split_counter++;
                            //printf("%d,%d ", split_counter, current_stream);
                        }
                        for(; split_counter<rozmiar_chunka; split_counter++)
                            fprintf(pliki[current_stream], "%s", "000");
                        split_counter=0;
                        current_stream=0;
                        //fprintf(pliki[current_stream], "%c", '\n');
                        lines_in_chunk++;
                        if(lines_in_chunk==rozmiar_chunka && lines_in_chunk+rozmiar_chunka*file_counter!=chunki*rozmiar_chunka)
                        {
                            lines_in_chunk=0;
                            file_counter++;
                            for(int j=0; j<chunki; j++)
                                fclose(pliki[j]);
                            for(int j=0; j<chunki; j++)
                            {
                                sprintf(t_filename, "%s_%d_%d.txt", "temp", j+1, file_counter+1);
                                pliki[j] = fopen(t_filename, "w");
                                //setbuf(pliki[j], buf[j]);
                            }
                        }
                    }
                }
            }
        }
    }
    for(; lines_in_chunk<rozmiar_chunka; lines_in_chunk++)
    {
        for(int i=0; i<chunki; i++)
        {
            for(int j=0; j<rozmiar_chunka; j++)
            {
                fprintf(pliki[i], "%s", "000");
            }
        }
    }
    for(int i=0; i<chunki; i++)
        fclose(pliki[i]);
    //fclose(maze_input);
    for(int i=0; i<chunki; i++)
    {
        for(int j=0; j<chunki; j++)
        {
        sprintf(t_filename, "%s_%d_%d.txt", "temp", j+1, i+1);
        sprintf(o_filename, "%d_%d.chunk", j+1, i+1);
        index=0;
        output_value=0;
        input=fopen(t_filename, "r");
        if(input==NULL) continue;
        //setbuf(input, buf[1]);
        fseek(input, 0, SEEK_END);
        if(ftell(input)==0)
        {
            fclose(input);
            remove(t_filename);
            continue; // aby nie tworzyło pustego outputu, choć kasować nie musi koniecznie w tym momencie
        }
        fseek(input, 0, SEEK_SET);
        output=fopen(o_filename, "wb");
        //setbuf(output, buf[0]);
        while((temp = fgetc(input)) != EOF)
        {
            if(temp=='1') output_value += 1 << (7-index);
            index++;
            if(index==8)
            {
                fwrite(&output_value, 1, 1, output);
                index=0;
                output_value=0;
            }
        }
        fwrite(&output_value, 1, 1, output);
        fclose(input);
        fclose(output);           
        }
    }
    return rozmiar_chunka;
}


void delete_chunks_bin(short int chunki)
{
    char d_filename[100];
    for(int i=0; i<chunki; i++)
        for(int j=0; j<chunki; j++)
        {
            sprintf(d_filename, "%d_%d.chunk", j+1, i+1);
            remove(d_filename);
        }
}
void delete_chunks_temp(short int chunki)
{
    char d_filename[100];
    for(int i=0; i<chunki; i++)
        for(int j=0; j<chunki; j++)
        {
            sprintf(d_filename, "%s_%d_%d.txt", "temp", j+1, i+1);
            remove(d_filename);
        }
}



//poniższe funkcje były tworzone jako prototypy/testy, są tutaj celem ułatwienia testów
//pierwsza zamienia plik z labiryntem na reprezentację binarną w formie tekstowej (jeden wielki chunk, pomimo argumentu chunki)
//druga kroi plik na kawałki 
//może są w nich jakieś memory leaki, ale nie będą one wykorzystywane w programie "docelowo"

short int podglad_bin(short int chunki , short int a, short int b, char * plik_wejsciowy)
{
    FILE * maze_input = fopen(plik_wejsciowy, "r");
    FILE * maze_output = fopen("test_full", "w");
    char temp;
    int x_counter = 0;
    int y_counter = 1;
    int first_line_skip=1;
    int buffer_size = 2*a;
    int ok=0;
    char buffer[buffer_size];
    while((temp = fgetc(maze_input)) != EOF)
    {
        x_counter++;
        if(temp=='\n')
        {
            y_counter++;
            x_counter=0;
            first_line_skip=0;
        }
        else
        {
            if(!first_line_skip)
            {
                if(((x_counter+y_counter)%2==1 && x_counter!=1))
                {
                    //fprintf(maze_output, "%c", temp);
                    //printf("ok");
                    //printf("%c", temp);
                    buffer[ok]=temp;
                    ok++;
                    if(ok==buffer_size)
                    {
                        ok=0;
                        for(int i=0; i<a; i++)
                        {
                            if(buffer[i] == ' ') fprintf(maze_output, "%c", '1');
                            else fprintf(maze_output, "%c", '0');
                            if(buffer[i+a] == ' ') fprintf(maze_output, "%c", '1');
                            else fprintf(maze_output, "%c", '0');
                            fprintf(maze_output, "%c", '0');
                            fprintf(maze_output, "%c", ' ');
                        }
                        fprintf(maze_output, "%c", '\n');
                    }
                }
            }

        }
    }
    fclose(maze_input);
    fclose(maze_output);
    return 0;
}

short int podziel_tekstowy(short int chunki , short int a, short int b, char * plik_wejsciowy)
{
    //chunki w linii
    //jeśli chunki^2>rozmiar pliku, czasami robią się puste pliki
    FILE * maze_input = fopen(plik_wejsciowy, "r");
    short int rozmiar_chunka;
    if(a<b)
    {
        rozmiar_chunka = b/chunki;
        if(chunki*rozmiar_chunka!=b) rozmiar_chunka++;
    }
    else
    {
        rozmiar_chunka = a/chunki;
        if(chunki*rozmiar_chunka!=a) rozmiar_chunka++;
    }

    FILE * pliki[chunki];
    char t_filename[100];
    for(int i=0; i<chunki; i++)
    {
        sprintf(t_filename, "%s_%d.txt", "test", i);
        pliki[i] = fopen(t_filename, "w"); //numerowane od zera (na razie)
    }
    char temp;
    int x_counter = 0;
    int current_stream=0;
    int y_counter = 0;
    int file_counter = 0;

        while((temp = fgetc(maze_input)) != EOF)
        {
            //printf("%c", temp);
            if(temp == '\n')
            {
                for(; x_counter<rozmiar_chunka; x_counter++)
                    fprintf(pliki[current_stream], "%c", 'X');
                fprintf(pliki[current_stream], "%c", '\n');
                current_stream = 0;
                x_counter = 0;
                y_counter++;
            }
            else
            {
                fprintf(pliki[current_stream], "%c", temp);
                x_counter++;
                if(x_counter==rozmiar_chunka)
                {
                    if(current_stream+1!=chunki)
                    {
                        fprintf(pliki[current_stream], "%c", '\n');
                        x_counter = 0;
                        current_stream++;
                    }
                }
            }
            if(y_counter==rozmiar_chunka && y_counter+rozmiar_chunka*file_counter!=chunki*rozmiar_chunka)
            {
                y_counter=0;
                file_counter++;
                current_stream=0;
                x_counter=0;
                for(int j=0; j<chunki; j++)
                    fclose(pliki[j]);
                for(int j=0; j<chunki; j++)
                {
                    sprintf(t_filename, "%s_%d.txt", "test", file_counter*chunki+j);
                    pliki[j] = fopen(t_filename, "w"); //numerowane od zera (na razie)
                }
            }
        }
        for(; y_counter<rozmiar_chunka; y_counter++)
        {
            for(int i=0; i<chunki; i++)
            {
                for(int j=0; j<rozmiar_chunka; j++)
                {
                    fprintf(pliki[i], "%c", 'X');
                }
                fprintf(pliki[i], "%c", '\n');
            }
        }
    return rozmiar_chunka;
}