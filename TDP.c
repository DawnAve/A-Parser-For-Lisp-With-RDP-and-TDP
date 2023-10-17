#include <stdbool.h>
#include <string.h>
#include "RDP.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char *nextTerminal; /* current position in input string */
TREE TDP_parseE(int** table, char* input);
TREE TDP_parseL(int** table, char* input);

int** create_table(void){
    int** table = malloc(9 * sizeof(int*));
    for(int i = 0; i < 9; i++)
        table[i] = malloc(5 * sizeof(int));

    
    int data[9][5] = {
        // (, ) lower case letters, numbers, space
        {2,0,1,1,0}, //Expression
        {0,0,3,4,0}, //Atom
        {0,0,5,0,0}, //Word letter + wordT
        {7,7,6,7,7}, //WordT
        {0,0,0,8,0}, //Number digit + numberT
        {10,10,10,9,10}, //NumberT 
        {11,12,0,0,0}, //List
        {14,0,14,14,0}, //Elements 
        {15,0,0,0,16} //Rest
    }; //X for no transitions

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 5; j++)
            table[i][j] = data[i][j];

    return table;
}

int input_to_number(char column){
    switch (column)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case' ':
        return 4;
    }
    if (islower(column)){
        return 2;
    }
    if (isdigit(column)){
        return 3;
    }
    return -1;
}

char* number_to_char(int opr){//convert a number operation to a string 
    switch (opr)
    {
    case 1:
        return "A\0"; // return Atom
    case 2:
        return "L\0"; //List
    case 3:
        return "W\0"; //Word
    case 4:
        return "N\0"; //Number
    case 5:
        return "ot\0"; //Letter and wordT   reversed for push
    case 6:
        return "W\0"; //Word
    case 7:
        return "e\0"; //Epsillon
    case 8:
        return "uD\0";  //Digit and numberT   reversed for push
    case 9:
        return "N\0";  //Number
    case 10:
        return "e\0"; //epsillon
    case 11:
        return "l(\0"; //( and elements   reversed for push
    case 12:
        return ")\0"; //)
    case 13:
        return "e\0"; //epsillon
    case 14:
        return "ER\0";    //expression and rest
    case 15:
        return "e\0";     //epsillon
    case 16:
        return "RES\0";   //space and expression and rest  reversed for push
    }
    return "X";
}

int char_to_number(char input){
    switch (input)
    {
    case 'E':
        return 0;
    case 'A':
        return 1;
    case 'W':
        return 2;
    case'o':
        return 3;
    case'N':
        return 4;
    case'u':
        return 5;
    case'L':
        return 6;
    case 'l':
        return 7;
    case'R':
        return 8;
    }
    return -1;
}
bool isTerminal(char C){
    //Check whether a symbol is terminal or not
    switch (C)
    {
    case '(':
    case ')':
    case 'D':
    case 't':
        return true;
    
    default:
        return false;
    }
}


TREE TDP_parseE(int** table, char* input){
    TREE root = NULL;
    Stack* stack = newStack('E');
    TREE start = makeNode1('E', makeNode0('A'));
    root = start;
    TREE parse = parseE(input);
    while (!isEmpty(stack)){
        char current = pop(stack);
        if (!isTerminal(current)){
            //If it is not a terminal, we go to the table to look for an int
            int row = char_to_number(current);
            //get the row number
            int column = input_to_number(*input);
            //get the column number
            char* new = number_to_char(table[row][column]);//the table is in reversed order already
            while (*new != '\0'){
                push(stack, *new);//push the characters into the stack
                
                *new+=1;
            }
            TREE temp = makeNode2(*nextTerminal, root, makeNode0(current));
            root = temp;
        }else{
            //means it is a terminal and we need to compare and comsume it
            if(lookahead(pop(stack))){
                makeNode1(*nextTerminal, makeNode0(current));
                *nextTerminal +=1;//move to the next character in the input
            }else{
                //does not match 
                if(pop(stack) == '*'){
                    makeNode0('*');//the top of the stack is epsillon
                }
                return NULL;
            }
            
        }
    }
    return parse;
}
TREE TDP_parseL(int** table, char* input){
    TREE root;
    Stack* stack = newStack('L');
    TREE start = makeNode3('L', makeNode0('('),makeNode0('e'), makeNode0(')'));
    root = start;
    TREE parse = parseL(input);
    while (!isEmpty(stack)){
        char current = pop(stack);
        if (!isTerminal(current)){
            //If it is not a terminal, we go to the table to look for an int
            int row = char_to_number(current);
            //get the row number
            int column = input_to_number(*input);
            //get the column number
            char* new = number_to_char(table[row][column]);//the table is in reversed order already
            while (*new != '\0'){
                push(stack, *new);//push the characters into the stack
                
                *new+=1;
            }
            TREE temp = makeNode2(*nextTerminal, root, makeNode0(current));
            root = temp;
        }else{
            //means it is a terminal and we need to compare and comsume it
            if(lookahead(pop(stack))){
                makeNode1(*nextTerminal, makeNode0(current));
                *nextTerminal +=1;//move to the next character in the input
            }else{
                //does not match 
                if(pop(stack) == '*'){
                    makeNode0('*');//the top of the stack is epsillon
                }
                return NULL;
            }
            
        }
    }
    return parse;
}
