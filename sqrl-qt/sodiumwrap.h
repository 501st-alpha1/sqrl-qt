#ifndef SODIUMWRAP_H
#define SODIUMWRAP_H

#include <QObject>
#include <QString>
#include <sodium.h>

class SodiumWrap : QObject {
  Q_OBJECT

 public:
  static unsigned char* getKeyFromQString(QString input);

  static const int SEED_LEN = crypto_sign_SEEDBYTES;
};

#endif
