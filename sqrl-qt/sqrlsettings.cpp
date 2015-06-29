#include "sqrlsettings.h"

SqrlSettings::SqrlSettings() {
}

bool SqrlSettings::getOption(const int optCode) {
  return (this->options & optCode) != 0;
}

QByteArray SqrlSettings::toQByteArray() {
  // FIXME: ensure that bytes are aligned correctly (pad with 0s if needed).
  QByteArray ret;
  ret.append("sqrldata");
  ret.append(157); // length of block
  ret.append(1); // type of block
  ret.append(45); // length of inner block

  qDebug() << ret;
  qDebug() << ret.size();

  return ret;
}
