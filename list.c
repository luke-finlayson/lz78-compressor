#ifndef STD
  #define STD
  #include "stdio.h"
  #include "stdlib.h"
  #include "stdbool.h"
#endif

struct ListNode {
  void* value;
  struct ListNode* next;
};

void printListIntNode(struct ListNode* node) {
  printf("L: { value: %d }\n", *(int*) node->value);
}

/**
 * Add a new node to the end of a list
*/
void listAdd(struct ListNode* root, void* value) {
  struct ListNode* current = root;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = (struct ListNode*) malloc(sizeof( struct ListNode ));
  current->next->value = value;
}

/**
 * Check if two lists are equal
*/
bool listCompare(struct ListNode* node1, struct ListNode* node2) {
  struct ListNode* current1 = node1;
  struct ListNode* current2 = node2;

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
void printIntList(struct ListNode* node) {
  struct ListNode* current = node;

  printf("[ ");

  while (current != NULL) {
    printf("%d ", *(int*) current->value);
    current = current->next;
  }

  printf("]\n");
}

/**
 * Returns the node in the list at the given index,
 * or NULL if it does not exist
*/
struct ListNode* getFromList(struct ListNode* root, int i) {
  struct ListNode* current = root;
  int currentIndex = 0;

  while (current != NULL) {
    if (currentIndex == i) {
      return current;
    }

    currentIndex++;
    current = current->next;
  }

  return NULL;
}
