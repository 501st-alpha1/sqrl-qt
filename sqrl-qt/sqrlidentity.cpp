#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>

SqrlIdentity::SqrlIdentity() {
}

bool SqrlIdentity::createIdentity() {
  // Creating a new SQRL identity.
  // **LOTS** of entropy here.
  qDebug() << "LOTS of entropy goes here";
  qDebug() << "Security warning: don't use this key for anything but testing!";

  qDebug() << "Currently the key is HARD-CODED!! Very bad!!";
  this->key = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);

  if (file.open(QIODevice::WriteOnly)) {
    QTextStream stream(&file);
    stream << this->key << endl;
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
  QString key;

  if (file.open(QIODevice::ReadOnly)) {
      QTextStream stream(&file);
      key = stream.readLine();
  }

  if (key.length() == 64) {
    this->key = key;
    return true;
  }
  else {
    return false;
  }
}

QString SqrlIdentity::getKey() {
  return this->key;
}
