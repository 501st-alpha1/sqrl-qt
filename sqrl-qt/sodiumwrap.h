#ifndef SODIUMWRAP_H
#define SODIUMWRAP_H

#include <QObject>
#include <QString>

class SodiumWrap : QObject {
  Q_OBJECT

 public:
  static unsigned char* getKeyFromQString(QString input);
};

#endif
