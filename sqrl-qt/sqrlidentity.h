#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

class SqrlIdentity {
 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  QByteArray getKey();
  QString getHexKey();
  QByteArray makeDomainPrivateKey(QString domain);
  QByteArray signMessage(QString message);

 private:
  QByteArray key;
};

#endif
