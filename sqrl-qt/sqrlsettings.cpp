#include "sqrlsettings.h"

SqrlSettings::SqrlSettings() {
}

bool SqrlSettings::getOption(const int optCode) {
  return (this->options & optCode) != 0;
}

QByteArray SqrlSettings::toQByteArray() {
  QByteArray ret;
  ret.append("sqrldata");
  ret.append(157); // length of block
  ret.append(1); // type of block

  qDebug() << ret;
  qDebug() << ret.size();

  return ret;
}
