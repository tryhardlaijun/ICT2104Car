#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include "coordinate.h"
#include "map.h"

typedef struct Node {
  int id;
  coordinate* data;
  struct Node* next;
}Node;


void freeList( Node* head);
void insertAtEnd(Node** head_ref,int id, coordinate* new_data);
Node* search(Node* head, int id);
void printLinkedlist(Node *p);