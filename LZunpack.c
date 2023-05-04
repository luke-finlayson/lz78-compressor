#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "utils.c"
#include "reader.c"
#include "writer.c"

int main() {
  fillBuffer();
  
  int k = 1;
  int numBits = 0;

  while (readerHas(numBits + 4)) {
    int phrase = read(numBits);
    int value = read(4);

    write(phrase, INTEGER_SIZE);
    write(value, BYTE_SIZE);

    ++k;
    numBits = ceil(log(k) / log(2));
  }

  flush();
}
