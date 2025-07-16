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
        stack->top[i] = malloc(sizeof(char) * STACK_ELEM_SIZE);
        if (!stack->top[i]) {
            printf("Stack Error: failed reallocating memory for a string");
            exit(1); 
        }
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
    stack->top = realloc(stack->top, stack->capacity * sizeof(char*));
    if (!stack->top) {
        printf("Stack Error: failed reallocating memory for top");
        exit(1);
    }

    // allocate space for the strings
    for(int i = stack->count + 1; i < stack->capacity; i++) {
        stack->top[i] = malloc(sizeof(char) * STACK_ELEM_SIZE);
        if (!stack->top[i]) {
            printf("Stack Error: failed reallocating memory for a string");
            exit(1); 
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
    printf("\n");
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