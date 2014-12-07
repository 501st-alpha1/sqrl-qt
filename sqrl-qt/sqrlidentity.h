#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

#include <QUrl>

class SqrlIdentity {
 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  QByteArray getKey();
  QString getHexKey();
  QByteArray makeDomainPrivateKey(QString domain);
  QByteArray signMessage(QString message, QByteArray privateKey);
  bool authenticate(QUrl url);

 private:
  QByteArray key;
};

#endif
