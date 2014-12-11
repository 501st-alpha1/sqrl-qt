#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

#include <QUrl>
#include <sodium.h>

class SqrlIdentity {
 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  unsigned char* getKey();
  QString getHexKey();
  QByteArray makeDomainPrivateKey(QString domain);
  QByteArray signMessage(QString message, QByteArray privateKey);
  bool authenticate(QUrl url);

 private:
  unsigned char* key;
};

#endif
