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
  unsigned char* signMessage(QString message, unsigned char* privateKey,
                             unsigned char* publicKey);
  bool authenticate(QUrl url);

 private:
  unsigned char* key;
};

#endif
