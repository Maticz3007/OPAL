//
// Created by Mateusz on 06.04.2024.
//

#include <stdio.h>
#include "RLE_decompressor.h"

short int RLE_decompression(char * b_filename) {
    int buffer;
    //int file_id;
    //char escape;
    short int columns;
    //short int lines;
    short int entry_x;
    short int entry_y;
    short int exit_x;
    short int exit_y;
    //reserved 12 bajtów
    int counter;
    //int solution_offset;
    char separator;
    char wall;
    char path;

    FILE * binary_input = fopen(b_filename, "rb");
    if (!binary_input)
    {
        //printf("Problem z plikiem binarnym!"); //komunikaty na potem
        return 20;
    }

    fread(&buffer, 4, 1, binary_input);
    //file_id = buffer;
    fread(&buffer, 1, 1, binary_input);
    //escape = buffer;
    fread(&buffer, 2, 1, binary_input);
    columns = buffer;
    fread(&buffer, 2, 1, binary_input);
    //lines = buffer;
    fread(&buffer, 2, 1, binary_input);
    entry_x = buffer;
    fread(&buffer, 2, 1, binary_input);
    entry_y = buffer;
    fread(&buffer, 2, 1, binary_input);
    exit_x = buffer;
    fread(&buffer, 2, 1, binary_input);
    exit_y = buffer;
    fseek(binary_input, 12, SEEK_CUR); //pomijam reserved
    fread(&buffer, 4, 1, binary_input);
    counter = buffer;
    fread(&buffer, 4, 1, binary_input);
    //solution_offset = buffer;
    fread(&buffer, 1, 1, binary_input);
    separator = buffer;
    fread(&buffer, 1, 1, binary_input);
    wall = buffer;
    fread(&buffer, 1, 1, binary_input);
    path = buffer;
    /*
    printf("Wartość file_id (hex): %x\n", file_id);
    printf("Wartość escape (hex): %x\n", escape);
    printf("Wartość columns: %d\n", columns);
    printf("Wartość lines: %d\n", lines);
    printf("Wartość entry_x: %d\n", entry_x);
    printf("Wartość entry_y: %d\n", entry_y);
    printf("Wartość exit_x: %d\n", exit_x);
    printf("Wartość exit_y: %d\n", exit_y);
    printf("Wartość counter: %d\n", counter);
    printf("Wartość solution_offset: %d\n", solution_offset);
    printf("Wartość separator: %c\n", separator);
    printf("Wartość wall: %c\n", wall);
    printf("Wartość path: %c\n", path);
    */
    FILE * test_output = fopen("maze_binary_source.txt" , "w"); //tymczasowy filepath

    char value;
    int count;
    int file_x=0;
    int file_y=1;

    for(int i=0; i<counter; i++)
    {
        fread(&buffer, 1, 1, binary_input);
        value = buffer;
        if(value!=separator) return -100;
        fread(&buffer, 1, 1, binary_input);
        value = buffer;
        if(value!=wall && value!=path)  return -101;
        fread(&buffer, 1, 1, binary_input);
        count = buffer;
       for(int j=-1; j<count; j++)
       {
           if (file_x==entry_x-1 && file_y==entry_y)
               fprintf(test_output, "%c", 'P');
           else
               if (file_x==exit_x-1 && file_y==exit_y)
                   fprintf(test_output, "%c", 'K');
               else
                   fprintf(test_output, "%c", value);
           file_x++;
           if(file_x == columns)
           {
               fprintf(test_output, "\n");
               file_x=0;
               file_y++;
           }

       }
    }

    fclose(binary_input);
    fclose(test_output);
    return 0;

}