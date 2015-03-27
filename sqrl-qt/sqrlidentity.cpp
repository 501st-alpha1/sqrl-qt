#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QStringList>
#include "sodiumwrap.h"

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
  QString seed = "0123456789ABCDEF0123456789ABCDEF";
  this->key = SodiumWrap::getKeyFromQString(seed);

  QString folderName = QDir::homePath() + "/.sqrl";
  if (!QDir(folderName).exists())
    QDir().mkdir(folderName);

  QString fileName = "ident.txt";
  QFile file(folderName + "/" + fileName);

  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);
    for (unsigned int i = 0; i < SodiumWrap::SEED_LEN; ++i) {
      out << (char)this->key[i];
    }
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

  if (file.size() == SodiumWrap::SEED_LEN) {
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      QString seed = in.readAll();
      this->key = SodiumWrap::getKeyFromQString(seed);
      file.close();

      return true;
    }
  }

  return false;
}

unsigned char* SqrlIdentity::getKey() {
  return this->key;
}

static QString getStringFromUnsignedChar(unsigned char *str) {
  QString result = "";

  for (unsigned int i = 0; i < SodiumWrap::SEED_LEN; i++) {
    QChar c = str[i];
    result.append(c);
  }

  return result;
}

QString SqrlIdentity::getHexKey() {
  return getStringFromUnsignedChar(this->key);
}

QByteArray SqrlIdentity::makeDomainPrivateKey(QString domain) {
  QByteArray key(getStringFromUnsignedChar(this->getKey()).toLocal8Bit());
  QByteArray out = SodiumWrap::hmacSha256(key, domain);

  return out;
}

QByteArray SqrlIdentity::signMessage(QString message,
                                     QByteArray privateKey,
                                     QByteArray publicKey) {
  QByteArray sig = SodiumWrap::signDetached(message, privateKey, publicKey);

  return sig;
}
