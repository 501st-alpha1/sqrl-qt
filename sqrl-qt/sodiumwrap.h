#ifndef SODIUMWRAP_H
#define SODIUMWRAP_H

#include <QObject>
#include <QString>
#include <sodium.h>

class SodiumWrap : QObject {
  Q_OBJECT

 public:
  static unsigned char* getKeyFromQString(QString input);
  static unsigned char* hmacSha256(unsigned char* key, QString message);
  static unsigned char* signDetached(QString message, QByteArray privateKey,
                                     unsigned char* publicKey);
  static QByteArray generatePrivateKey(QByteArray seed);
  static unsigned char* ed25519PrivateKeyToPublicKey(QByteArray privateKey);

  static const int SEED_LEN = crypto_sign_SEEDBYTES;
  static const int SK_LEN = crypto_sign_SECRETKEYBYTES;
  static const int PK_LEN = crypto_sign_PUBLICKEYBYTES;
  static const int SIG_LEN = crypto_sign_BYTES;
};

#endif
