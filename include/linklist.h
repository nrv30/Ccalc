#include "../include/calc.h"

#pragma once
typedef struct Node  {
    char* data; // data
    struct Node* next;
} Node;

// typedef struct Equation {
//     String
// }Equation;

void insert(Node* data, int n);
void printList();
void delete(int n); 
void pushBack(Node* node);
void initNode(Node** node, char* data);
void clearList();
