#include <math.h>
#include "reader.c"
#include "writer.c"

/**
 * Takes output from the LZ Encoder and packs the
 * phrase numbers into the least amount of bits.
 * Uses log2(k) many bits to write the phrase number(s).
 * 
 * Created by Luke Finlayson, 1557835
 */
int main() {
  // Fill the initial read buffer
  fillBuffer();

  // Keep track of how many lines we have read (k)
  int k = 1;
  int numBits = 0;

  while (readerHas(BYTE_SIZE * 5)) {
    // Read in the next LZ78 entry
    int phrase = read(INTEGER_SIZE);
    int value = read(BYTE_SIZE);

    write(phrase, numBits);
    write(value, 4);

    // Calculate the amount of bits needed to represent
    // the next phrase number -> bits = log2(k)
    ++k;
    numBits = ceil(log(k) / log(2));
  }

  flush();
  
  return 0;
}
