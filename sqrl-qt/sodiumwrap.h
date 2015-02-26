#ifndef SODIUMWRAP_H
#define SODIUMWRAP_H

#include <QString>

class SodiumWrap : QObject {
  Q_OBJECT

 public:
  unsigned char* getKeyFromQString(QString input);
};

#endif
