#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

char buffer[5000];   // Global buffer to store the contents of the try.c file
char *file = NULL;

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        printf("enter a source file as command\n", argv[0]);
        return 1;
    }

    file = argv[1];

    FILE* fptr = fopen(file, "r");
    if (!fptr) 
    {
        printf("Error: Could not open file '%s'\n", file);
        return 1;
    }

    int i = 0;
    char ch;
    while ((ch = fgetc(fptr)) != EOF && i < sizeof(buffer) - 1) 
    {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
    fclose(fptr);

    lexi();  

    return 0;
}
