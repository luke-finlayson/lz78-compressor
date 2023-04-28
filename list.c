#include <stdbool.h>

struct Node {
  int value;
  struct Node* next;
};

/**
 * Add a new node to the end of a list
*/
void listAdd(struct Node* root, int value) {
  struct Node* current = root;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = (struct Node*) malloc(sizeof( struct Node ));
  current->next->value = value;
}

/**
 * Check if two lists are equal
*/
bool listCompare(struct Node* node1, struct Node* node2) {
  struct Node* current1 = node1;
  struct Node* current2 = node2;

  while (current1 != NULL && current2 != NULL) {
    if (current1->value != current2->value) {
      return false;
    }
    
    current1 = current1->next;
    current2 = current2->next;
  }

  return (current1 == NULL && current2 == NULL);
}

/**
 * Output the contents of a list to stdout
*/
void printList(struct Node* node) {
  struct Node* current = node;

  printf("[ ");

  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }

  printf("]\n");
}
