#ifndef SQRLIDENTITY_H
#define SQRLIDENTITY_H

class SqrlIdentity {
 public:
  SqrlIdentity();
  bool createIdentity();
  bool loadIdentity();
  QString getKey();

 private:
  QString key;
};

#endif
