#ifndef HEADER_H
#define HEADER_H



void key(int line, int col, char* word);
void lexi();
int isliteral(int line, int col, char* word);
int isfloat(int line, int col, char* word);
int ischar(int line, int col, char* word);
int isnum(int line, int col, char* word);

void err_id(int line, int col, char* word);
int valid_id(char* word);
int err_num(int line, int col, char* word);
int err_float(int line, int col, char* word);
int err_s(int line, int col, char* buffer, int i);

extern char *file;



#endif