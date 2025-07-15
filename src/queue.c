#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "../include/queue.h"
const int ELEM_SIZE = 64;

void allocQueue(Queue* queue) 
{
    assert(queue->capacity != 0);
    queue->head_pt = (char**)malloc(queue->capacity * sizeof(char*));

    for (int i = 0; i < queue->capacity; i++) 
    {
        queue->head_pt[i] = (char*)malloc(sizeof(char) * ELEM_SIZE);
        assert(queue->head_pt[i] != 0 && queue->head_pt[i] != NULL);
    }
}

void enQueue(Queue* queue, char* data) 
{
    if (queue->head == -1 && queue->tail == -1) {
        queue->head = 0;
        queue->tail = 0;
    }

    if(queue->tail == queue->capacity) 
    {
        resizeQueue(queue); 
    }

    memmove(queue->head_pt[queue->tail], data, strlen(data) + 1);    
    queue->tail++;
}

void resizeQueue(Queue* queue) 
{
    printf("reached this on iteration %d\n", queue->tail);
    queue->capacity *= 2;
    char** temp = (char**) realloc(queue->head_pt, queue->capacity);
    if (temp == NULL) {
        printf("stack overflow error\n");
        exit(1);
    }
    queue->head_pt = temp;

    for(int i = queue->head; i < queue->capacity-1; i++) {
        char* temp_pt = (char*)malloc(sizeof(char) * ELEM_SIZE);
        if (temp_pt == NULL) {
            printf("Error: failed reallocating memory");
            exit(1); 
        } else {
            queue->head_pt[i] = temp_pt;
        }
    }
}

char* deQueue(Queue* queue) 
{
    assert(queue->tail != -1); // empty queue

    char* temp = queue->head_pt[queue->head];
    queue->head++;
    
    if (queue->head == queue->tail + 1) {
        queue->tail = -1;
        queue->head = 0;
    }
    return temp;
}

void printQueue(Queue* queue) 
{
    for (int i = queue->head; i < queue->tail; i++) {
        // printf("%d ", i);
        printf("%s ", queue->head_pt[i]);
    }
}

// void freeQueue(Queue* queue) {
//     // for (int i = queue->head; i < queue->tail; i++) {
//     //     free(queue->head_pt[i]);
//     // }

//     // free (queue->head_pt);
//     printf("HEAD: %d\n", queue->head);
//     printf("Tail: %d\n", queue->tail);
// }