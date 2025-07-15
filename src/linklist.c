#include <stdio.h>
#include <stdlib.h>

#include "../include/linklist.h"

//insert node at position n
void insert(Node* node, int n) 
{
    // make temp1 the new head
    if(n == 1) {
        if (head == NULL) {
            head = node;
            return;
        }
        node->next = head;
        head = node;
        return;
    }
    
    Node* temp = head;
    for (int i = 0; i < n-2; i++) 
    {
        temp = temp->next;
    }

    node->next = temp->next;
    temp->next = node;    
}

void delete(int n) 
{
    Node* temp1 = head;

    // if deleting the head node
    // make the second node head
    if(n == 1) {
        head = temp1->next;
    }
    else {
        for(int i = 0; i < n-2; i++) {
            temp1 = temp1->next;
        }
        // temp2 holds address of node to delete
        Node* temp2 = temp1->next;
        temp1->next = temp2->next;
        free(temp2);
    }
}

void printList() 
{
    Node* temp = head;
    while(temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void pushBack(Node* node) 
{
    if (head == NULL) {
        head = node;
        return;
    }
    Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
    node->next = NULL;
}

void initNode(Node** node, char* data) 
{
    *node = (Node*)malloc(sizeof(Node));

    (*node)->data = *data;
    (*node)->next = NULL;

}

void clearList() 
{
    Node* temp = head;
    while(temp != NULL) {
        Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    head = NULL;
}