#include "header.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


// Check if identifier is valid
int valid_id(char* word)
{
    if(word[0] == '\0')
    {
        return 0;
    }
    if(isdigit(word[0]))
    {
        return 0;
    }
    return 1;
}

// Error check for invalid identifier
void err_id(int line, int col, char* word)
{
    printf("try.c:%d:%d: error: invalid identifier '%s'\n", line, col, word);
    exit(0);
}

// Error check for numeric constants
int err_num(int line, int col, char* word)
{
    int i = 0;

    // Hexadecimal check
    if(word[0] == '0' && (word[1] == 'x' || word[1] == 'X'))
    {
        for(i = 2; word[i] != '\0'; i++)
        {
            if(!((word[i] >= '0' && word[i] <= '9') || (word[i] >= 'A' && word[i] <= 'F') ||
                 (word[i] >= 'a' && word[i] <= 'f')))
            {
                printf("try.c:%d:%d: error: invalid suffix '%c' on integer constant\n", line, col+i, word[i]);
                exit(0);
            }
        }
        return 1;
    }

    // Binary check
    if(word[0] == '0' && (word[1] == 'b' || word[1] == 'B'))
    {
        for(i = 2; word[i] != '\0'; i++)
        {
            if(word[i] != '0' && word[i] != '1')
            {
                printf("try.c:%d:%d: error: invalid digit '%c' in binary constant\n", line, col+i, word[i]);
                exit(0);
            }
        }
        return 1;
    }

    // Octal check
    if(word[0] == '0' && word[1] != '\0')
    {
        for(i = 1; word[i] != '\0'; i++)
        {
            if(word[i] < '0' || word[i] > '7')
            {
                printf("try.c:%d:%d: error: invalid digit '%c' in octal constant\n", line, col+i, word[i]);
                exit(0);
            }
        }
        return 1;
    }

    // Decimal  check
    for(i = 0; word[i] != '\0'; i++)
    {
       if(!isdigit(word[i]))
        {
            err_id(line, col, word);  // alpha in decimal means invalid identifier
        }
    }

    return 1;
}

//error check for float constant
int err_float(int line, int col, char* word)
{
    int i = 0;
    int dot_count = 0;
    if (word[0] == '.' && word[1] == '\0')
    {
        printf("try.c:%d:%d: error: invalid float constant '%s'\n", line, col, word);
        exit(0);
    }

    while (word[i] != '\0')
    {
        if (word[i] == '.')
        {
            dot_count++;
            if (dot_count > 1)
            {
                printf("try.c:%d:%d: error: invalid float constant '%s'\n", line, col, word);
                exit(0);
            }
        }
        else if (isdigit(word[i]))
        {
            
            if (word[i + 1] == 'f' || word[i + 1] == 'F')
            {
                if (word[i + 2] == '\0')
                {
                    
                    return 1;
                }
                else
                {
                    printf("try.c:%d:%d: error: invalid suffix '%c' on floating constant\n",
                           line, col, word[i + 2]);
                    exit(0);
                }
            }
        }
        else
        {
           
            printf("try.c:%d:%d: error: invalid suffix '%c' on floating constant\n",
                   line, col, word[i]);
            exit(0);
        }

        i++;
    }

    return 1;
}


// Error handling for symbols, braces, and parentheses
int err_s(int line, int col, char* buffer, int i)
{
    // Check ()
    if(buffer[i] == '(')
    {
        int j = i + 1;
        int paren_count = 1; 
        while(buffer[j] != '\0')
        {
            if(buffer[j] == '(') 
            {
                paren_count++;
            }
            else if(buffer[j] == ')') 
            {
                paren_count--;
            }

            if(paren_count == 0) 
            {
                break;
            }
            j++;
        }

        if(paren_count != 0)
        {
            printf("try.c:%d:%d: error: expected ')' before ';' token\n", line, col);
            exit(0);
        }
        return 1;
    }

    // Check braces {}
    if(buffer[i] == '{')
    {
        int j = i + 1;
        int brace_count = 1; 
        while(buffer[j] != '\0')
        {
            if(buffer[j] == '{')
            {
                 brace_count++;
            }
            else if(buffer[j] == '}') 
            {
                brace_count--;
            }

            if(brace_count == 0) 
            {
                break;
            }
            j++;
        }

        if(brace_count != 0)
        {
            printf("try.c:%d:%d: error: expected '}' before end of input\n", line, col);
            exit(0);
        }
        return 1;
    }

    // Check brackets []
    if(buffer[i] == '[')
    {
        int j = i + 1;
        int bracket_count = 1; 
        while(buffer[j] != '\0')
        {
            if(buffer[j] == '[')
            {
                 bracket_count++;
            }
            else if(buffer[j] == ']')
            {
                 bracket_count--;
            }

            if(bracket_count == 0)
            {
                 break;
            }
            if(buffer[j] == '=' || buffer[j] == '{' || buffer[j] == ';' || buffer[j] == '\n')
            {
                 break;
            }
            j++;
        }

        if(bracket_count != 0)
        {
            printf("try.c:%d:%d: error: expected ']' before ';' token\n", line, col);
            exit(0);
        }
    }

    return 1;
}
