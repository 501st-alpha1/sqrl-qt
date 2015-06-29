#include "sqrlsettings.h"

SqrlSettings::SqrlSettings() {
}

bool SqrlSettings::getOption(const int optCode) {
  return (this->options & optCode) != 0;
}

QByteArray SqrlSettings::toQByteArray() {
  QByteArray ret;
  ret.append(157);

  qDebug() << ret;

  return ret;
}
