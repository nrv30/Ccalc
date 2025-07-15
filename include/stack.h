#include <stdbool.h>

#pragma once
typedef struct 
{
    int count;
    int capacity;
    char** top; // pointer to first element in array of char*'s
} Stack;

void allocStack(Stack* stack);
void push(Stack* stack, char* op);
char* pop(Stack* stack);
char* tostring(Stack* stack);
void resizeStack(Stack* stack);
char* peek(Stack* stack);
bool isEmpty(Stack* stack);

