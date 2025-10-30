#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"



extern char buffer[5000]; 


void lexi()
{
 int line = 1, col = 0;
    char word[50];
    int k = 0;

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        char ch = buffer[i];
        col++;

       
        if(ch == '\n')
        {
            line++;
            col = 0;
            continue;
        }

        // Skip preprocessor lines
        if(ch == '#')
        {
            while(buffer[i] != '\n' && buffer[i] != '\0')
                i++;
            continue;
        }

        // Skip single-line comments
        if(ch == '/' && buffer[i+1] == '/')
        {
            i += 2;
            while(buffer[i] != '\n' && buffer[i] != '\0')
               i++;
            continue;
        }

        // String literal check
        if(ch == '"')
        {
            k = 0;
            word[k++] = ch;
            i++;
            while(buffer[i] != '"' && buffer[i] != '\0' && buffer[i] != '\n')
            {
                word[k++] = buffer[i++];
            }
            if(buffer[i] == '"')
            {
                word[k++] = buffer[i];
                i++;
                word[k] = '\0';
                printf("Literal: %s\n", word);

                 if(buffer[i] == ')') 
                 {
                     printf("Symbol: %c\n", buffer[i]);
                 }

                continue;
            }
            else
            {
                word[k] = '\0';
                printf("try.c:%d:%d: error: missing terminating '\"' character\n", line, col);
                exit(0);
            }
        }

        // Char literal 
        if(ch == '\'')
        {
            if(buffer[i+2] != '\'')
            {
                printf("try.c:%d:%d: error: missing terminating ' character\n", line, col);
                exit(0);
            }
            word[0] = buffer[i];
            word[1] = buffer[i+1];
            word[2] = buffer[i+2];
            word[3] = '\0';
            i += 2;
            printf("Char const: %s\n", word);
            continue;
        }

        // Alphanumeric/identifier/number
        if(isalpha(ch) || ch == '_' || isdigit(ch))
        {
            k = 0;
            int dot = 0;

            while(isalnum(buffer[i]) || buffer[i] == '_' || buffer[i] == '.')
            {
                if(buffer[i] == '.')
                {
                    if(dot) 
                    {
                        break;
                    } 
                    dot = 1;
                }
                word[k++] = buffer[i++];
            }
            i--;
            word[k] = '\0';

            if(isdigit(word[0]))
            {
                if(dot)
                {
                    if(isfloat(line, col, word))
                    {
                    printf("Float const: %s\n", word);
                    }
                }
                else if(isnum(line, col, word))
                {
                    printf("Numeric const: %s\n", word);
                }
            }
            else
            {
                key(line, col, word);
            }
            continue;
        }

        // Symbols with error checking
        if(ch == '{' || ch == '(' || ch == '[')
        {
            if(err_s(line, col, buffer, i))
            {
                printf("Symbol: %c\n", ch);
                continue;
            }
        }

        // Closing symbols
        if(strchr("})],;", ch) != NULL)
        {
            printf("Symbol: %c\n", ch);
            continue;
        }

        // Operators
        if(strchr("+-*/%=&|!<>", ch) != NULL)
        {
            // check for double-character operators
            if(strchr("+-*/%=&|!<>", buffer[i+1]) != NULL)
            {
                printf("Operator: %c%c\n", ch, buffer[i+1]);
                i++;
            }
            else
            {
                printf("Operator: %c\n", ch);
            }
            continue;
        }

        // Skip whitespace
        if(isspace(ch))
            continue;
    }


}
