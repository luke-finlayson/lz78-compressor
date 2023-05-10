#include "list.c"

struct TrieNode {
  struct TrieNode* children[16];
  int parent;
  int value;
  int index;
};

void printTrieNode(struct TrieNode* node) {
  printf("T: { index: %d, parent: %d, value: %d }\n", node->index, node->parent, node->value);
}

/**
 * Insert a word into the Trie
 * @param word The word to insert into the Trie
 * @return Will return the deepest node of the resulting word in the Trie
 */
struct TrieNode* insertIntoTrie(struct TrieNode* root, struct ListNode* word) {
  struct TrieNode* current = root;
  struct TrieNode* newNode = NULL;

  // Traverse the tree as each symbol of the word is read
  while (word != NULL) {
    // If a TrieNode for the current symbol does not exist - then create one
    if (current->children[*(int*) word->value] == NULL) {
      newNode = (struct TrieNode*) malloc(sizeof( struct TrieNode ));
      newNode->value = *(int*) word->value;
      newNode->parent = current->index;
      newNode->index = root->value;

      current->children[*(int*) word->value] = newNode;

      // Increment the next index value
      root->value = root->value + 1;
    }

    current = current->children[*(int*) word->value];
    word = word->next;
  }

  return newNode;
}

/**
 * Check to see if a word exists in the tree
 * @param root The root node of the Trie
 * @param word The word to search for
 * @return Returns the trie node that was found
 */
struct TrieNode* findInTrie(struct TrieNode* root, struct ListNode* word) {
  struct TrieNode* currentTrieNode = root;
  struct ListNode* currentListNode = word;

  while (currentListNode != NULL) {
    int value = *(int*) currentListNode->value;

    if (currentTrieNode->children[value] == NULL) {
      return NULL;
    }

    currentTrieNode = currentTrieNode->children[value];
    currentListNode = currentListNode->next;
  }

  return currentTrieNode;
}
