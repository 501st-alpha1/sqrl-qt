#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QtCrypto>
#include <QStringList>
#include <sodium.h>

SqrlIdentity::SqrlIdentity() {
}

/*
 * Generate a new SQRL identity.
 * Need to add **LOTS** of entropy here.
 */
bool SqrlIdentity::createIdentity() {
  qDebug() << "LOTS of entropy goes here";
  qDebug() << "Security warning: don't use this key for anything but testing!";

  qDebug() << "Currently the key is HARD-CODED!! Very bad!!";
  QString seed = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  unsigned char actualSeed[crypto_sign_SEEDBYTES];
  memcpy(actualSeed, seed.data(), crypto_sign_SEEDBYTES);
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  crypto_sign_seed_keypair(pk, this->key, actualSeed);

  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);

  if (file.open(QIODevice::WriteOnly)) {
    file.write((char*)this->key, crypto_sign_SECRETKEYBYTES);
    file.close();
  }
  else {
    qDebug() << "Error: couldn't open file for writing.";
  }

  return true;
}

/*
 * Load a SQRL identity from file.
 * In case of failure, return false, otherwise, return true.
 */
bool SqrlIdentity::loadIdentity() {
  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);

  if (file.size() == crypto_sign_SECRETKEYBYTES) {
    if (file.open(QIODevice::ReadOnly)) {
      unsigned char* temp = (unsigned char*)file.readAll().data();
      memcpy(this->key, temp, crypto_sign_SECRETKEYBYTES);

      return true;
    }
  }

  return false;
}

unsigned char* SqrlIdentity::getKey() {
  return this->key;
}

/*
 * Via. http://stackoverflow.com/a/12417415/2747593
 */
QString getStringFromUnsignedChar(unsigned char *str) {
  QString s;
  QString result = "";

  // Print String in Reverse order....
  for (unsigned int i = 0; i < crypto_sign_SECRETKEYBYTES; i++) {
      s = QString("%1").arg(str[i],0,16);

      if(s.length() == 1)
        result.append("0");

      result.append(s);
  }

  return result;
}

QString SqrlIdentity::getHexKey() {
  return getStringFromUnsignedChar(this->key);
}

QByteArray SqrlIdentity::makeDomainPrivateKey(QString domain) {
  QCA::Initializer init;

  QByteArray arg = domain.toLocal8Bit();

  if (!QCA::isSupported("hmac(sha256)")) {
    qDebug() << "hmac(sha256) is not supported!";
    return NULL;
  }
  else {
    QCA::MessageAuthenticationCode hmacObject("hmac(sha256)",QCA::SecureArray());

    QCA::SymmetricKey keyObject(this->key);

    hmacObject.setup(this->key);

    QCA::SecureArray converter(arg);

    hmacObject.update(converter);

    QCA::SecureArray result = hmacObject.final();

    return result.toByteArray();
  }
}

QByteArray SqrlIdentity::signMessage(QString message, QByteArray privateKey) {
  if (sodium_init() == -1) {
    qDebug() << "Error: sodium_init failed.";
    return NULL;
  }

  // Prepare the private key
  unsigned char sk[crypto_sign_SECRETKEYBYTES];
  memcpy(sk, privateKey.data(), crypto_sign_SECRETKEYBYTES);

  // Now the public key
  unsigned char pk[crypto_sign_PUBLICKEYBYTES];
  crypto_sign_ed25519_sk_to_pk(pk, sk);

  qDebug() << "pk " << pk;
  qDebug() << "sk " << sk;

  unsigned char sealedMessage[crypto_sign_BYTES + message.length()];
  unsigned long long sealedMessageLen;

  crypto_sign(sealedMessage, &sealedMessageLen,
              (unsigned char*)message.toAscii().constData(), message.length(),
              sk);

  unsigned char unsealedMessage[message.length()];
  unsigned long long unsealedMessageLen;

  if (crypto_sign_open(unsealedMessage, &unsealedMessageLen, sealedMessage, sealedMessageLen, pk) != 0)
    qDebug() << "fail!";
  else
    qDebug() << "win";

  return NULL;
}

bool SqrlIdentity::authenticate(QUrl url) {
  QByteArray domainPrivateKey = this->makeDomainPrivateKey(url.host());

  QString message = url.host() + url.path() + "?nut=" + url.queryItemValue("nut");
  QByteArray signature = this->signMessage(message, domainPrivateKey);

  return false;
}
