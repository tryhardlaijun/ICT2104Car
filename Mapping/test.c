#include "test.h"

void insertAtEnd( Node** head_ref,int id, coordinate* new_data) {
   Node* new_node = ( Node*)malloc(sizeof( Node));
   Node* last = *head_ref;

  new_node->data = new_data;
  new_node ->id  = id;
  new_node->next = NULL;

  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }

  while (last->next != NULL) last = last->next;

    last->next = new_node;
    return;
}

void freeList( Node* head)
{
    Node* tmp;
   while (head != NULL)
    {
        
       tmp = head;
       free(tmp->data);
       head = head->next;
       free(tmp);
    }
}

Node* search(Node* head, int id)
{
    Node* current = head; // Initialize current
    while (current != NULL) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}


// print the linked list value
void printLinkedlist(Node *p) {
    int count = 0;
  while (p != NULL) {
    count++;
    printf("THIS IS MAP %d\n",count);
    printMap(p->data);
    p = p->next;
  }
}
// int main() {
//    Node* head = NULL;    
//     freeList(head);
// }
