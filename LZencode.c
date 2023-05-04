#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "utils.c"
#include "reader.c"
#include "writer.c"

#include "list.c"
#include "trie.c"

int main() {
  // Fill the initial read buffer
  fillBuffer();

  struct ListNode* word = NULL;
  struct TrieNode* root = (struct TrieNode*) malloc(sizeof( struct TrieNode ));
  root->value = 1;

  while (readerHas(4)) {
    int hex = read(4);
    
    // Add the symbol to the current phrase - creating the list if it is empty
    if (word == NULL) {
      word = (struct ListNode*) malloc(sizeof( struct ListNode ));
      word->value = hex;
    }
    else {
      listAdd(word, hex);
    }

    // Add the word to the trie if it doesn't exist
    if (findInTrie(root, word) == NULL) {
      struct TrieNode* node = insertIntoTrie(root, word);

      // Output the new LZ78 entry
      write(node->parent, INTEGER_SIZE);
      write(node->value, BYTE_SIZE);

      // Clear the word and start reading in a new phrase
      word = NULL;
    }
  }

  // Output the remaining word as if it was a new entry
  if (word != NULL) {
    struct TrieNode* node = findInTrie(root, word);

    write(node->parent, INTEGER_SIZE);
    write(node->value, BYTE_SIZE);
  }

  flush();
}
