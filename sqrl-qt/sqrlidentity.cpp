#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QStringList>
#include <QTime>
#include "sodiumwrap.h"

SqrlIdentity::SqrlIdentity() {
}

QByteArray SqrlIdentity::getRandomQByteArray() {
  QByteArray ret;

  for (int i = 0; i < SodiumWrap::SEED_LEN; ++i) {
    int rand = qrand() % 16;
    ret.append(QByteArray::number(rand, 16));
  }

  return ret;
}

/*
 * Generate a new SQRL identity.
 * Need to add **LOTS** of entropy here.
 */
bool SqrlIdentity::createIdentity() {
  qDebug() << "LOTS of entropy goes here";
  qDebug() << "Security warning: don't use this key for anything but testing!";

  QTime time = QTime::currentTime();
  qsrand((uint) time.msec());
  QByteArray seed = this->getRandomQByteArray();

  qDebug() << "The generated seed is:" << seed;

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

QByteArray SqrlIdentity::getIdentityUnlockKey() {
  //FIXME
  QByteArray seed = "FEDCBA9876543210FEDCBA9876543210";
  QByteArray privateKey = SodiumWrap::generatePrivateKey(seed);

  return privateKey;
}

QByteArray SqrlIdentity::getIdentityLockKey() {
  QByteArray privateKey = this->getIdentityUnlockKey();
  QByteArray publicKey = SodiumWrap::ed25519PrivateKeyToPublicKey(privateKey);

  return publicKey;
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
