#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

#include <QNetworkReply>

class SqrlIdentity : QObject {
  Q_OBJECT

 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  QByteArray getKey();
  QByteArray getIdentityLockKey();
  QByteArray makeDomainPrivateKey(QString domain);
  QByteArray signMessage(QString message, QByteArray privateKey,
                         QByteArray publicKey);

 private:
  QByteArray key;
  QByteArray ilk;
};

#endif
