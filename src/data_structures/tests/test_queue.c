#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/queue.h"

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

    char* data[] = {
    strdup("1"), strdup("2"), strdup("3"), strdup("4"), strdup("5"),
    strdup("6"), strdup("7"), strdup("8"), strdup("9"), strdup("10")
};
    for (int i = 0; i < 5; i++) {
    enQueue(&queue, data[i]);
    }

    //freeQueue(&queue);    
    //printQueue(&queue);
    return 0;
}