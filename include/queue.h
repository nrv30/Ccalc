#include <stdbool.h>

#pragma once
typedef struct Queue
{
    int tail;
    int head;
    int capacity;
    char** head_pt;
} Queue;

void freeQueue(Queue* queue);
void allocQueue(Queue* queue);
void enQueue(Queue* queue, char* data);
void resizeQueue(Queue* queue);
char* deQueue(Queue* queue);
void printQueue(Queue* queue);