#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

#include <QNetworkReply>

class SqrlIdentity : QObject {
  Q_OBJECT

 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  unsigned char* getKey();
  QString getHexKey();
  QByteArray makeDomainPrivateKey(QString domain);
  unsigned char* signMessage(QString message, QByteArray privateKey,
                             QByteArray publicKey);

 private:
  unsigned char* key;
};

#endif
