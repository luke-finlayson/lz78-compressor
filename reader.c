// Main read readBuffer
long readBuffer;
int readSize = 0;

/**
 * Returns the amount of unused bits in the read readBuffer
*/
int readCapacity() {
  return (sizeof( long ) * BYTE_SIZE) - readSize;
}

/**
 * Check if there are some bits available to read in the readBuffer
*/
bool readerHas(int numBits) {
  return readSize >= numBits;
}

/**
 * Reads a byte from standard input
*/
int8_t readNext() {
  int8_t buf[1];
  fread(buf, 1, 1, stdin);

  return buf[0];
}

/**
 * Fills the read readBuffer with as many bytes possible
*/
void fillBuffer() {
  while (readCapacity() >= BYTE_SIZE) {
    int8_t byte = readNext();
    
    // Do not read if EOF has been reached
    if (feof(stdin)) {
      break;
    }
    
    readBuffer <<= BYTE_SIZE;
    readBuffer |= byte & 0xFF;
    readSize += BYTE_SIZE;
  }
}

/**
 * Read a given number of bits from standard input
*/
int read(int numBits) {
  readSize -= numBits;

  int value = readBuffer >> readSize;
  readBuffer &= createMask(readSize);

  fillBuffer();

  return value & createMask(numBits);
}
