#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"
const int QUEUE_ELEM_SIZE = 64;

void allocQueue(Queue* queue) 
{
    assert(queue->capacity != 0);
    queue->head_pt = malloc(sizeof(char*) * queue->capacity);

    for (int i = 0; i < queue->capacity; i++) 
    {
        queue->head_pt[i] = malloc(sizeof(char) * QUEUE_ELEM_SIZE);
        if (!queue->head_pt[i]) {
            printf("Queue Error: failed reallocating memory for a string");
            exit(1); 
        }
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

    strcpy(queue->head_pt[queue->tail], data);   
    queue->tail++;
}

void resizeQueue(Queue* queue) 
{
    queue->capacity *= 2;
    queue->head_pt = realloc(queue->head_pt, sizeof(char*) * queue->capacity);
    if (!queue->head_pt) {
        printf("Queue Error: failed reallocating memory for head");
        exit(1);
    }

    for(int i = queue->tail; i < queue->capacity; i++) {
        queue->head_pt[i] = malloc(sizeof(char) * QUEUE_ELEM_SIZE);
        if (!queue->head_pt[i]) {
            printf("Queue Error: failed reallocating memory for a string");
            exit(1); 
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

    printf("\n");
}

void freeQueue(Queue* queue) {
    for (int i = queue->head; i < queue->tail; i++) {
        free(queue->head_pt[i]);
    }

    free (queue->head_pt);
    //printf("HEAD: %d\n", queue->head);
    //printf("Tail: %d\n", queue->tail);
}