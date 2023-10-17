#ifndef _TDP_h
#define _TDP_h

TREE TDP_parseE(int** table, char* input);
TREE TDP_parseL(int** table, char* input);
int** create_table(void);
char *nextTerminal;
int input_to_number(char column);
char* number_to_char(int opr);
int char_to_number(char input);
bool isTerminal(char C);

#endif