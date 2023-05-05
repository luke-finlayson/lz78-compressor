#ifndef UTILS
  #define UTILS
  #include "utils.c"
#endif

long writeBuffer = 0;
int writeSize;

/**
 * Write a integer out of the writeBuffer
*/
void flushByte() {
  // Can't flush if we don't have a whole byte in the writeBuffer
  if (writeSize < BYTE_SIZE) {
    return;
  }

  writeSize -= BYTE_SIZE;

  int buf[] = { (writeBuffer >> writeSize) & 0xFF };
  fwrite(buf, 1, 1, stdout);

  writeBuffer &= createMask(writeSize);
}

/**
 * Returns the amount of null bits in the write writeBuffer
*/
int writeCapacity() {
  return LONG_SIZE - writeSize;
}

/**
 * Write a given number of bits to standard output
 * 
 * @param value The integer containing the binary value to write
 * @param numBits The number of bits to write
*/
void write(int value, int numBits) {
  while (numBits > writeCapacity()) {
    flushByte();
  }

  value &= createMask(numBits);
  writeBuffer <<= numBits;
  writeBuffer |= value;

  writeSize += numBits;
}

/**
 * Output the remaining bytes in the buffer to standard output
*/
void flush() {
  // Pad the end of the buffer if it does not fit nicely into bytes
  int remainderBits = writeSize % 8;

  if (remainderBits != 0 ) {
    write(0, BYTE_SIZE - remainderBits);
  }

  while (writeSize != 0) {
    flushByte();
  }
}
