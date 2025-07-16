#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"
#include "queue.h"

 // gcc -Wall -Wextra -g -o calccli calc.c stack.c queue.c

typedef enum  {
    ADD = 0, 
    SUB = 0,
    MULT = 1,
    DIV = 1,
    PAREN = 2,
    INVALID = -1
} opPrec;

// returns number of tokens or -1 if fails
int make_OutputQueue(Stack* stack, Queue* outQueue);
int getPrec(char* tok);
void cleanStack(Stack* stack, Queue* outQueue);
void compare_operators(int prec, Stack* stack, Queue* outQueue);

int main(void) 
{
    Stack stack;
    stack.capacity = 5;
    allocStack(&stack);

    Queue outQueue;
    outQueue.capacity = 5;
    allocQueue(&outQueue);

    const int minLen = 3; // smallest equation
    int tokCount = 0;
    int loopCount = 0; 
    do {
        if (loopCount > 0 && tokCount != 0) {
            printf("invalid input re-enter\n");
        } else if (loopCount > 0 && tokCount == 0) {
            return 0;
        }
        loopCount++;
        stack.count = -1;
        outQueue.head = -1;
        outQueue.tail = -1;
        tokCount = make_OutputQueue(&stack, &outQueue); 
    } while (tokCount < minLen || tokCount == -1 || tokCount == 0);

    return 0;
}

// 3 + 4 * ( 2 - 1 ) * 6 + 8
// answer: 3421-*6*+8+

int make_OutputQueue(Stack* stack, Queue* outQueue) 
{
    const int maxEquation = 1024;
    char* equation = malloc(sizeof(char)* maxEquation);
    
    int tokCount = 0;
    char* tok;

    printf(">> ");
    fgets(equation, maxEquation, stdin);
    equation[strlen(equation)-1] = '\0'; // get rid of newline
    if (equation == NULL) exit(1);

    printf("%s\n", equation);

    for( tok = strtok_r(equation," ", &equation); tok!=NULL ; tok=strtok_r(NULL," ", &equation)) {
        tokCount++;
        float num;
        // if token is number enqueue it
        if ((num = atof(tok)) != 0.0 || strcmp(tok, "0") == 0) {
            enQueue(outQueue, tok);
        // token is operator
        } else {
            int prec = getPrec(tok);
            // printf("%d\n", prec);
            switch(prec) 
            {
                // One of these: *, /, +, -
                case 1:
                case 2:
                    compare_operators(prec, stack, outQueue);
                    push(stack, tok);
                    break;
                case 3:
                    push(stack, tok);
                    break;
                case 4:
                    do {
                        enQueue(outQueue, pop(stack));
                    } while(strcmp(peek(stack), "(") != 0); // this
                    pop(stack); // get rid of open paren
                    // printQueue(outQueue);
                    // printStack(stack);
                    break;
                case 0:
                    printf("Quitting Successfully");
                    free(equation);
                    return 0;
                case -1:
                    printf("error: invalid symbol '%s'", tok);
                    free(equation);
                    return -1;
            }
                 
        }

        printf("tok: %s\n", tok);
        printf("iteration: %d ", tokCount);
        printf("stack is ");
        printStack(stack);
        printf("queue is ");
        printQueue(outQueue);
        printf("------\n");
    }
    free(equation);

    if (!isEmpty(stack)) 
    {
        cleanStack(stack, outQueue);
    }
    
    // freeStack(&stack);
    return tokCount;
    
}

int getPrec(char* tok) 
{
    if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0) {
        return 1;
    } else if (strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0) {
        return 2;
    } else if (strcmp(tok, "(") == 0) {
        return 3;
    } else if (strcmp(tok, ")") == 0) {
        return 4;
    }
    else if (strcmp(tok, "Q\n") == 0 || strcmp(tok, "q\n") == 0) {
        return 0;
    }
    else return -1;
}

void cleanStack(Stack* stack, Queue* outQueue) 
{
    for (int i = stack->count - 1; i > -1; i--) {
        enQueue(outQueue, stack->top[i]);
    }
}

void compare_operators(int prec, Stack* stack, Queue* outQueue) {
    if (!isEmpty(stack)) {
        int next_prec = getPrec(peek(stack));
    // enqueue the previous next if it was smaller or the same precedence
        while (prec <= next_prec && next_prec != 3) {
            enQueue(outQueue, pop(stack));
            compare_operators(prec, stack, outQueue);
        }
    }
}
