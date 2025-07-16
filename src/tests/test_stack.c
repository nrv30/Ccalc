#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/stack.h"


int main(void) {

    printf("------Testing stack------\n");
    Stack stack = {
        .capacity  = 5,
        .count = -1,
    };
    allocStack(&stack);

    char string[] = "a,b,c,d,e,f,g,h,i,j,";
    printf("%s\n", string);

    for (char* data = strtok(string, ","); data != NULL; data = strtok(NULL, ",") ) {
        push(&stack, data);
    }

    if (stack.count !=10) {
        printf("FAILED: test1: wrong count");
        return 1;
    } else {
        printf("PASSED: test 1\n");
    }

    char* stack_buf = tostring(&stack);
    printf("%s\n", stack_buf);
    if (strcmp(stack_buf, "stack: abcdefghij") != 0) {
        printf("FAILED: test2: printing the stack\n");
        return 1;
    } else {
        printf("PASSED: test 2\n");
        free(stack_buf);
    }

    if (strcmp(peek(&stack), "j") != 0) {
        printf("FAILED: test 3: Peek Function\n");
        return 1;
    } else {
        printf("PASSED: test 3\n ");
    }

    char* elem = pop(&stack);
    if (strcmp(elem, "j") != 0 && stack.count != 9 && strcmp(tostring(&stack), "abcdefghi") != 0) {
        printf("FAILED: test4: Pop\n");
    } else {
        printf("PASSED: test 4\n");
    }

    printf("-----PASSED: Tests All------");

    return 0;

}