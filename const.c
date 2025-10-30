#include "header.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>


// Check if a word is a valid numeric constant
int isnum(int line, int col, char* word)
{
    if((err_num(line, col, word)) == 0)     // return 0 if error found else 1
    {
        return 0;      
    }

    return 1;
}

// Check if a word is a valid float constant
int isfloat(int line, int col, char* word)
{

    if((err_float(line, col, word)) == 0)
    {
        return 0;
    }

    int i = 0;
    int dot = 0;
    while(word[i])
    {
        if(word[i] == '.')
        {
            dot = 1;
        }
        if(dot > 1)
        {
            return 0;
        }
        else if(word[i] < '0' || word[i] > '9')
        {
            if(word[i] != 'f' && word[i+1] != '\0')  
            {
                i++;
                continue;
            }
            return 0;
        }
        i++;
    }
    if(dot == 1)
    {
        return 1;
    }
    return 1;    // valid float
}
