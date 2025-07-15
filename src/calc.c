#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/stack.h"
#include "../include/queue.h"

 // gcc -Wall -Wextra -g -o calccli calc.c stack.c queue.c

typedef enum  {
    ADD = 0, 
    SUB = 0,
    MULT = 1,
    DIV = 1,
    PAREN = 2,
    INVALID = -1
} opPrec;

int make_OutputQueue(Stack* stack, Queue* outQueue);
int getPrec(const char* tok);
void cleanStack(Stack* stack, Queue* outQueue);

int main(void) 
{
    Stack stack;
    stack.capacity = 5;
    allocStack(&stack);

    Queue outQueue;
    outQueue.capacity = 5;
    allocQueue(&outQueue);

    const int minLen = 3;
    int tokCount = 0;
    int loopCount = 0; 
    do {
        if (loopCount > 0 && tokCount != 0) {
            printf("invalid input re-enter\n");
        } else if (loopCount > 0 && tokCount == 0) {
            return 0;
        }
        loopCount++;
        stack.count = 0;
        outQueue.head = 0;
        outQueue.tail = -1;
        tokCount = make_OutputQueue(&stack, &outQueue); 
    } while (tokCount < minLen || tokCount == -1 || tokCount == 0);

     printf("-----testing-----");
    //printStack(stack);
    printQueue(&outQueue);

    return 0;
}

// 3 + 4 * ( 2 - 1 ) * 6 + 8
// answer: 3421-*6*+8+

// returns number of tokens or -1 if fails
int make_OutputQueue(Stack* stack, Queue* outQueue) 
{
    const int maxEquation = 1024;
    char* buf = (char*)malloc(sizeof(maxEquation));

    int tokCount = 0;
    char* tok;

    // puts the equation in buff
    printf(">> ");
    fgets(buf, maxEquation, stdin);
    buf[strlen(buf)-1] = '\0'; // get rid of newline
    if (buf == NULL) exit(1);

    printf("%s\n", buf);

    for( tok = strtok_r(buf," ", &buf); tok!=NULL ; tok=strtok_r(NULL," ", &buf)) {
        printf("tok: %s\n", tok);
        tokCount++;
        float num;
        // if token is number enqueue it
        if ((num = atof(tok)) != 0.0 || strcmp(tok, "0") == 0) {
            enQueue(outQueue, tok);
        // token is operator
        } else {
            int prec = getPrec(tok);
            switch(prec) 
            {
                // *, /, +, -
                case 1:
                case 2:
                    if (!isEmpty(stack)) {
                        int next_prec = getPrec(peek(stack));
                        // enqueue the previous next if it was smaller or the same precedence
                        while (prec <= next_prec && next_prec != 3) {
                            enQueue(outQueue, pop(stack));
                            next_prec = getPrec(peek(stack));
                        }
                    }
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
                    printQueue(outQueue);
                    printStack(stack);
                    break;
                case 0:
                    printf("Quitting Successfully");
                    return 0;
                case -1:
                    printf("error: invalid symbol '%s'", tok);
                    return -1;
            }
                 
        }
        if (tokCount == 10) {
            char** p;
            printf("head: %d, tail: %d: ", outQueue->head, outQueue->tail);
            for (int i = outQueue->head; i < outQueue->tail; i++) {
            p = (char** )((outQueue->head_pt) + i);
            assert(p != NULL);
            // printf("%p\n", p);
            }

            printf("p = %p, *p = %p\n", (void*)p, (void*)*p);
            char c = **p;
            // printf("%c", c);
            exit(1);

        }
        printf("iteration: %d ", tokCount);
        printf("stack is ");
        printStack(stack);
        printf("\n");
        printf("queue is ");
        printQueue(outQueue);
        printf("\n");
    }
    free(buf);

    if (!isEmpty(stack)) 
    {
        cleanStack(stack, outQueue);
    }
    
    return tokCount;
    
}

int getPrec(const char* tok) 
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
    else if (tok[0] == 'Q' || tok[0] == 'q') {
        return 0;
    }
    else {return -1;}
}

void cleanStack(Stack* stack, Queue* outQueue) 
{
    for (int i = stack->count - 1; i > -1; i--) {
        printf("stack at top %s ", stack->top[i]);
        enQueue(outQueue, stack->top[i]);
    }
}
