#ifndef SQRLAUTHENTICATOR_H
#define SQRLAUTHENTICATOR_H

#include <QUrl>
#include "sqrlidentity.h"

class SqrlAuthenticator : QObject {
  Q_OBJECT

 public:
  SqrlAuthenticator(SqrlIdentity* ident);
  bool query(QUrl url);
  QString base64url(QString input);
  QString unbase64url(QString input);
  QString trim(QString input);
  QMap<QString,QString> parseArgs(QString input);
  int intToHex(int input);

  public slots:
    void replyFinished(QNetworkReply* reply);

 private:
    SqrlIdentity* ident;
};

#endif
