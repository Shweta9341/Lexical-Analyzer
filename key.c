#include "header.h"
#include <stdio.h>
#include <string.h>


// keyword  and identifier check
void key(int line, int col, char* word)
{
    const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"};

    int n = sizeof(keywords) / sizeof(keywords[0]);
    int count = 0;

    for(int i = 0; i < n; i++) 
    {
        if(strcmp(word, keywords[i]) == 0)
        {
            count = 1;
            break;
        }
    }

    if(count == 1)
    {
        printf("Keyword: %s\n", word);
    }
    else
    {
        if(valid_id(word)  == 1) // check if identifier is valid or not
        {
            printf("Identifier: %s\n", word);
        }
        else
        {
            err_id(line, col, word);     //check for invalid indentifier
        }
    }
}
