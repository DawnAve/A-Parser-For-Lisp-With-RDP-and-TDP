#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Stack {
    char* array;
    int top;
} Stack;

// 创建一个新的栈节点
Stack* newStack(char data) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = 0;
    stack->array = (char*) malloc(100 * sizeof(char));
    stack->array[0] = data;
    return stack;
}

// 检查栈是否为空
int isEmpty(Stack* stack) {
    return stack->top+1;
}

// 向栈中添加元素
void push(Stack* stack, char data) {
    stack->top+=1;
    stack->array[stack->top] = data;
}

// 从栈中移除元素
char pop(Stack* stack) {
    if (stack->top == -1){
        return -1;
    }
    char temp = stack->array[stack->top];
    stack->top -=1;
    return temp;
    
}
