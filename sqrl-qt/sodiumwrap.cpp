#include <sodium.h>
#include "sodiumwrap.h"
#include <QDebug>

static QByteArray getQByteArrayFromUnsignedChar(unsigned char* input) {
  QByteArray ret((char*)input);
  return ret;
}

static unsigned char* getUnsignedCharFromString(QString str) {
  int len = str.length();
  unsigned char* result = new unsigned char[len];
  for (int i = 0; i < len; ++i) {
    result[i] = (unsigned char)str.at(i).toAscii();
  }
  return result;
}

unsigned char* SodiumWrap::getKeyFromQString(QString input) {
  return getUnsignedCharFromString(input);
}

unsigned char* SodiumWrap::hmacSha256(QByteArray key, QString message) {
  unsigned char* out = new unsigned char[crypto_auth_hmacsha256_BYTES];
  unsigned char* in = getUnsignedCharFromString(message);
  unsigned char* actualKey = new unsigned char[SodiumWrap::SEED_LEN];
  memcpy(actualKey, key, SodiumWrap::SEED_LEN);

  crypto_auth_hmacsha256(out, in, message.length(), actualKey);

  if (crypto_auth_hmacsha256_verify(out, in, message.length(), actualKey) != 0) {
    qDebug() << "Error! HMAC failed!";
    return NULL;
  }

  return out;
}

QByteArray SodiumWrap::signDetached(QString message,
                                    QByteArray privateKey,
                                    QByteArray publicKey) {
  unsigned char* actualMessage = getUnsignedCharFromString(message);
  unsigned char* out = new unsigned char[SodiumWrap::SIG_LEN];
  unsigned char* actualPrivateKey = new unsigned char[SodiumWrap::SK_LEN];
  memcpy(actualPrivateKey, privateKey, SodiumWrap::SK_LEN);
  unsigned char* actualPublicKey = new unsigned char[SodiumWrap::PK_LEN];
  memcpy(actualPublicKey, publicKey, SodiumWrap::PK_LEN);

  crypto_sign_detached(out, NULL, actualMessage, message.length(), actualPrivateKey);

  if (crypto_sign_verify_detached(out, actualMessage, message.length(),
                                  actualPublicKey) != 0) {
    qDebug() << "Signing failed!";
    return NULL;
  }

  return getQByteArrayFromUnsignedChar(out);
}

QByteArray SodiumWrap::generatePrivateKey(QByteArray seed) {
  // Prepare the seed
  unsigned char actualSeed[SodiumWrap::SEED_LEN];
  memcpy(actualSeed, seed, SodiumWrap::SEED_LEN);

  // Prepare public and private keys
  unsigned char* privateKey = new unsigned char[SodiumWrap::SK_LEN];
  unsigned char publicKey[SodiumWrap::PK_LEN];

  // Generate keys from seed
  crypto_sign_seed_keypair(publicKey, privateKey, actualSeed);

  return getQByteArrayFromUnsignedChar(privateKey);
}

QByteArray SodiumWrap::ed25519PrivateKeyToPublicKey(QByteArray privateKey) {
  unsigned char* publicKey = new unsigned char[SodiumWrap::PK_LEN];
  unsigned char* actualPrivateKey = new unsigned char[SodiumWrap::SK_LEN];
  memcpy(actualPrivateKey, privateKey, SodiumWrap::SK_LEN);

  crypto_sign_ed25519_sk_to_pk(publicKey, actualPrivateKey);

  QByteArray ret = getQByteArrayFromUnsignedChar(publicKey);

  return ret;
}
