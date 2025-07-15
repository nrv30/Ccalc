#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/stack.h"

void test_stack();

int main(void) {
    test_stack();
    return 0;
}

void test_stack() {
printf("------Testing stack------\n");
    Stack stack = {
        .capacity  = 5,
        .count = 0,
    };
    allocStack(&stack);
    
    char* answer[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for (int i = 0; i < 10; i++) {
        push(&stack, answer[i]);
    }

    if (stack.count !=10) {
        printf("FAILED: test1: wrong count");
        exit(1);
    } else {
        printf("PASSED: test 1\n");
    }

    char* stack_buf = tostring(&stack);
    printf("%s\n", stack_buf);
    if (strcmp(stack_buf, "stack: 0123456789") != 0) {
        printf("FAILED: test2: printing the stack\n");
        exit(1);
    } else {
        printf("PASSED: test 2\n");
        free(stack_buf);
    }

    if (strcmp(peek(&stack), "9") != 0) {
        printf("FAILED: test 3: Peek Function\n");
        exit(1);
    } else {
        printf("PASSED: test 3\n ");
    }

    char* elem = pop(&stack);
    if (strcmp(elem, "9") != 0 && stack.count != 9 && strcmp(tostring(&stack), "012345678") != 0) {
        printf("FAILED: test4: Pop\n");
    } else {
        printf("PASSED: test 4\n");
    }

    printf("-----PASSED: Tests All------");
}