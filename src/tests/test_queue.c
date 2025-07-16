#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "queue.h"

int main(void) {
    printf("------test Queue-----\n");
    Queue queue = {
        .capacity = 5,
        .tail = -1,
        .head = -1,
    };
    allocQueue(&queue);

    assert(queue.head_pt != NULL);
    printf("PASSED: allocating memory\n");

    
    char string [] = "a,b,c,d,e,f,g,h,i,j,k,";

    for (char* data = strtok(string, ","); data != NULL; data = strtok(NULL, ",") ) {
        // printf("%s ", data);
        enQueue(&queue, data);
        printQueue(&queue);
    }

    // printQueue(&queue);
    // freeQueue(&queue);    
    return 0;
}