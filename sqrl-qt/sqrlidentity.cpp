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
  QByteArray seed = "0123456789ABCDEF0123456789ABCDEF";
  this->key = seed;

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
      QByteArray seed = in.readAll().toAscii();
      this->key = seed;
      file.close();

      return true;
    }
  }

  return false;
}

QByteArray SqrlIdentity::getKey() {
  return this->key;
}

QByteArray SqrlIdentity::makeDomainPrivateKey(QString domain) {
  QByteArray out = SodiumWrap::hmacSha256(this->key, domain);

  return out;
}

QByteArray SqrlIdentity::signMessage(QString message,
                                     QByteArray privateKey,
                                     QByteArray publicKey) {
  QByteArray sig = SodiumWrap::signDetached(message, privateKey, publicKey);

  return sig;
}
