#include <sodium.h>
#include "sodiumwrap.h"
#include <QDebug>

static QByteArray getQByteArrayFromUnsignedChar(unsigned char* input, int len) {
  QByteArray ret;

  for (int i = 0; i < len; ++i) {
    ret.append((char)input[i]);
  }

  // printf("unsigned char input: ");
  // for (int i = 0; i < ret.length(); ++i) {
  //   printf("%02x", (unsigned char)input[i]);
  // }
  // printf("\n");
  // qDebug() << "QByteArray output:";
  // qDebug() << ret.toHex();
  return ret;
}

static unsigned char* getUnsignedCharFromQByteArray(QByteArray input) {
  unsigned char* out = new unsigned char[input.length()];
  memcpy(out, input, input.length());

  // qDebug() << "QByteArray input:";
  // qDebug() << input.toHex();

  // printf("unsigned char output: ");
  // for (int i = 0; i < input.length(); ++i) {
  //   printf("%02x", (unsigned char)out[i]);
  // }
  // printf("\n");

  return out;
}

static unsigned char* getUnsignedCharFromString(QString str) {
  int len = str.length();
  unsigned char* result = new unsigned char[len];
  for (int i = 0; i < len; ++i) {
    result[i] = (unsigned char)str.at(i).toAscii();
  }
  return result;
}

QByteArray SodiumWrap::hmacSha256(QByteArray key, QString message) {
  unsigned char* out = new unsigned char[crypto_auth_hmacsha256_BYTES];
  unsigned char* in = getUnsignedCharFromString(message);
  unsigned char* actualKey = getUnsignedCharFromQByteArray(key);

  crypto_auth_hmacsha256(out, in, message.length(), actualKey);

  if (crypto_auth_hmacsha256_verify(out, in, message.length(), actualKey) != 0) {
    qDebug() << "Error! HMAC failed!";
    return NULL;
  }

  return getQByteArrayFromUnsignedChar(out, crypto_auth_hmacsha256_BYTES);
}

QByteArray SodiumWrap::signDetached(QString message,
                                    QByteArray privateKey,
                                    QByteArray publicKey) {
  unsigned char* actualMessage = getUnsignedCharFromString(message);
  unsigned char* out = new unsigned char[SodiumWrap::SIG_LEN];
  unsigned char* actualPrivateKey = getUnsignedCharFromQByteArray(privateKey);
  unsigned char* actualPublicKey = getUnsignedCharFromQByteArray(publicKey);

  crypto_sign_detached(out, NULL, actualMessage, message.length(), actualPrivateKey);

  if (crypto_sign_verify_detached(out, actualMessage, message.length(),
                                  actualPublicKey) != 0) {
    qDebug() << "Signing failed!";
    return NULL;
  }

  return getQByteArrayFromUnsignedChar(out, SodiumWrap::SIG_LEN);
}

QByteArray SodiumWrap::generatePrivateKey(QByteArray seed) {
  // Prepare the seed
  unsigned char* actualSeed = getUnsignedCharFromQByteArray(seed);

  // Prepare public and private keys
  unsigned char* privateKey = new unsigned char[SodiumWrap::SK_LEN];
  unsigned char publicKey[SodiumWrap::PK_LEN];

  // Generate keys from seed
  crypto_sign_seed_keypair(publicKey, privateKey, actualSeed);

  return getQByteArrayFromUnsignedChar(privateKey, SodiumWrap::SK_LEN);
}

QByteArray SodiumWrap::ed25519PrivateKeyToPublicKey(QByteArray privateKey) {
  unsigned char* publicKey = new unsigned char[SodiumWrap::PK_LEN];
  unsigned char* actualPrivateKey = getUnsignedCharFromQByteArray(privateKey);

  crypto_sign_ed25519_sk_to_pk(publicKey, actualPrivateKey);

  QByteArray ret = getQByteArrayFromUnsignedChar(publicKey, SodiumWrap::PK_LEN);

  return ret;
}
