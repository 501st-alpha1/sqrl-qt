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
  QByteArray key((char*)this->getKey());

  if (!QCA::isSupported("hmac(sha256)")) {
    qDebug() << "hmac(sha256) is not supported!";
    return NULL;
  }
  else {
    QCA::MessageAuthenticationCode hmacObject("hmac(sha256)",QCA::SecureArray());

    QCA::SymmetricKey keyObject(key);

    hmacObject.setup(key);

    QCA::SecureArray converter(arg);

    hmacObject.update(converter);

    QCA::SecureArray result = hmacObject.final();

    return result.toByteArray();
  }
}

QByteArray SqrlIdentity::signMessage(QString message, QByteArray key) {
  if (sodium_init() == -1) {
    qDebug() << "Error: sodium_init failed.";
    return NULL;
  }

  // Prepare the private key
  unsigned char privateKey[crypto_sign_SECRETKEYBYTES];
  memcpy(privateKey, key, crypto_sign_SECRETKEYBYTES);

  // Now the public key
  unsigned char publicKey[crypto_sign_PUBLICKEYBYTES];
  crypto_sign_ed25519_sk_to_pk(publicKey, privateKey);

  /*
   * Debugging
   */
  printf("public key ");
  for (unsigned int i = 0; i < crypto_sign_PUBLICKEYBYTES; ++i) {
    printf("%02x", (unsigned char)publicKey[i]);
  }
  printf("\n");

  printf("private key ");
  for (unsigned int i = 0; i < crypto_sign_SECRETKEYBYTES; ++i) {
    printf("%02x", (unsigned char)privateKey[i]);
  }
  printf("\n");
  /*
   * End debugging
   */

  unsigned char* actualMessage = (unsigned char*)message.toAscii().constData();
  unsigned char sig[crypto_sign_BYTES];

  crypto_sign_detached(sig, NULL, actualMessage, message.length(), privateKey);

  if (crypto_sign_verify_detached(sig, actualMessage, message.length(),
                                  publicKey) != 0)
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
