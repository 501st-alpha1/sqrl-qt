#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

class SqrlIdentity {
 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  QByteArray getKey();
  QString getHexKey();

 private:
  QByteArray key;
};

#endif
