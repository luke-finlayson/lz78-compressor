#include "reader.c"
#include "writer.c"
#include "trie.c"

/**
 * Reads from standard input and uses a Trie to encode
 * the hexadecimal values using LZ78, outputting the
 * entries to standard output.
 * 
 * Output format: [32bit phrase number][8 bit hexadecimal mismatched symbol]
 * (5 bytes total per entry)
 * 
 * Created by Luke Finlayson, 1557835
 */
int main() {
  // Fill the initial read buffer
  fillBuffer();

  // Create the linked list to keep track of the longest matching phrase
  struct ListNode* word = NULL;
  struct TrieNode* root = (struct TrieNode*) malloc(sizeof( struct TrieNode ));
  root->value = 1;

  // Read input file nibble by nibble until the end of the file is reached
  while (readerHas(4)) {
    int* hex = (int*) malloc(sizeof( int ));
    *hex = read(4);
    
    // Add the symbol to the current phrase - creating the list if it is empty
    if (word == NULL) {
      word = (struct ListNode*) malloc(sizeof( struct ListNode ));
      word->value = (void*) hex;
    }
    else {
      listAdd(word, (void*) hex);
    }

    // Add the word to the trie if it doesn't exist
    if (findInTrie(root, word) == NULL) {
      struct TrieNode* node = insertIntoTrie(root, word);

      // Output the new LZ78 entry
      write(node->parent, INTEGER_SIZE);
      write(node->value, BYTE_SIZE);

      // Clear the word and start reading in a new phrase
      word = clearList(word);
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
