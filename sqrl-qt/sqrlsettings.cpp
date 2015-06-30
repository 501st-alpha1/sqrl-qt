#include "sqrlsettings.h"

SqrlSettings::SqrlSettings(SqrlIdentity* ident) {
  this->ident = ident;
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
  // TODO 12 bytes aes-gcm iv init vector
  // TODO 16 bytes scrypt random salt
  // TODO 1 byte scrypt log n factor
  // TODO 4 bytes scrypt iteration count
  ret.append(this->options);
  ret.append(4); // hint length (1 byte)
  ret.append(3); // pw verify seconds (1 byte)
  ret.append(10); // idle timeout minutes (2 bytes)

  ret.append(this->ident->getKey()); // identity master key
  // TODO encrypted identity lock key
  // TODO encrypted previous identity master key

  // TODO verification tag

  qDebug() << ret;
  qDebug() << ret.size();

  return ret;
}
