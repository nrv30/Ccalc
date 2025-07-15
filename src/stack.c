#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "../include/stack.h"

const int STACK_ELEM_SIZE = 64;

void allocStack(Stack* stack) 
{
    assert(stack->capacity != 0);
    stack->top = malloc(stack->capacity * sizeof(char*));

    for (int i = 0; i < stack->capacity; i++) 
    {
        stack->top[i] = (char*)malloc(sizeof(char) * STACK_ELEM_SIZE);
    }
}

void push(Stack* stack, char* op) 
{
    int index;
    if (stack->count == -1) {
        index = 0;
        stack->count = 0;
    } else {
        if(stack->count == stack->capacity) {
            resizeStack(stack); 
        }
        index = stack->count;
        
    }

    index = stack->count;
    memmove(&(stack->top[index]), &op, sizeof(op));
    stack->count++;
    
    
}

char* pop(Stack* stack) 
{
    assert(stack->count!=0);

    char* op = stack->top[stack->count-1];
    stack->count--;
    return op;
}

void resizeStack(Stack* stack) 
{
    // make space for twice the number of strings
    stack->capacity *= 2;
    char** temp = (char**) realloc(stack->top, stack->capacity * sizeof(char*));
    if (temp == NULL) {
        printf("stack overflow error\n");
        exit(1);
    } else {
        stack->top = temp;
    }

    // allocate space for the strings
    for(int i = stack->count + 1; i < stack->capacity; i++) {
        char* temp_pt = (char*)malloc(sizeof(char) * STACK_ELEM_SIZE);
        if (temp_pt == NULL) {
            printf("Error: failed reallocating memory");
            exit(1); 
        } else {
            stack->top[i] = temp_pt;
        }
    }
}

// for the tests
char* tostring(Stack* stack) 
{
    char* stack_buf = malloc(sizeof(char) * 256);
    strcpy(stack_buf, "stack: ");
    for (int i = 0; i < stack->count; i++) {
        char* temp = stack->top[i];
        strcat(stack_buf, temp);
    }
    return stack_buf;
}

void printStack(Stack* stack) 
{
    for (int i = 0; i < stack->count; i++) {
        printf("%s, ", stack->top[i]);
    }
}

char* peek(Stack* stack) 
{
    return stack->top[stack->count-1];
}

bool isEmpty(Stack* stack) 
{
    if (stack->count == -1) return true;
    else return false;
}