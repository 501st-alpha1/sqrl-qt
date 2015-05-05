#ifndef SQRLAUTHENTICATOR_H
#define SQRLAUTHENTICATOR_H

#include <QUrl>
#include "sqrlidentity.h"

class SqrlAuthenticator : QObject {
  Q_OBJECT

 public:
  SqrlAuthenticator(SqrlIdentity* ident);
  bool sqrlCommand(QString command, QUrl url);
  bool query(QUrl url);
  bool ident(QUrl url);
  QString getNextSqrlUrl();
  QString base64url(QString input);
  QString unbase64url(QString input);
  QString trim(QString input);
  QMap<QString,QString> parseArgs(QString input);
  int intToHex(int input);

  bool querySuccess;

  public slots:
    void replyFinished(QNetworkReply* reply);

 private:
    SqrlIdentity* identity;
    int tif;
    QString qry;
    QString sfn;
    QString domain;
};

#endif
