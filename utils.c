#ifndef STD
  #define STD
  #include "stdio.h"
  #include "stdlib.h"
  #include "stdbool.h"
#endif

const int BYTE_SIZE = 8;
const int INTEGER_SIZE = 32;
const int LONG_SIZE = 64;

void bin(unsigned n)
{
  int j = 0;
  unsigned i;
  for (i = 1 << 31; i > 0; i = i / 2)
      (n & i) ? printf("1") : printf("0");
}

long createMask(int numBits) {
  if (numBits <= 0) {
    return 0;
  }

  long mask = 1;

  for (int i = 1; i < numBits; ++i) {
    mask <<= 1;
    mask |= 1;
  }

  return mask;
}
