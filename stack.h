#ifndef _stack_h
#define _stack_h

typedef struct Stack {
    char* array;
    int top;
} Stack;

Stack* newStack(char data);
int isEmpty(Stack* stack);
void push(Stack* stack, char data);
char pop(Stack* stack);

#endif