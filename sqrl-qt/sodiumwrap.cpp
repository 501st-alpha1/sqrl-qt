#include <sodium.h>
#include "sodiumwrap.h"

static unsigned char* getUnsignedCharFromString(QString str, int len) {
  unsigned char* result = new unsigned char[crypto_sign_SEEDBYTES];
  for (int i = 0; i < len; ++i) {
    result[i] = (unsigned char)str.at(i).toAscii();
  }
  return result;
}

static unsigned char* SodiumWrap::getKeyFromQString(QString input) {
  return getUnsignedCharFromString(input, input.length());
}
