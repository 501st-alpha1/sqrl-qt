#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QtCrypto>

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
  const char* key = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  QByteArray keyBytes = QByteArray::fromHex(key);
  this->key = keyBytes;

  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);

  if (file.open(QIODevice::WriteOnly)) {
    file.write(this->key);
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
  QByteArray key;

  if (file.open(QIODevice::ReadOnly)) {
    key = file.readLine();
  }

  if (key.size() == 32) {
    this->key = key;
    return true;
  }
  else {
    return false;
  }
}

QByteArray SqrlIdentity::getKey() {
  return this->key;
}

QString SqrlIdentity::getHexKey() {
  return this->key.toHex();
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
