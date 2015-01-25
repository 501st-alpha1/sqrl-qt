#include "sqrlidentity.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QtCrypto>
#include <QStringList>
#include <sodium.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

const QString CRLF = "\r\n";

// Transaction Information Flags
const int TIF_IDK_MATCH = 0x01;
const int TIF_PDK_MATCH = 0x02;
const int TIF_IP_MATCH = 0x04;
const int TIF_ACC_ENABLED = 0x08;
const int TIF_ACC_LOGGED_IN = 0x10;
const int TIF_TRANSIENT_FAILURE = 0x20;
const int TIF_COMMAND_FAILED = 0x40;
const int TIF_SQRL_FAILURE = 0x80;
const int TIF_STALE_NUT = 0x100;

SqrlIdentity::SqrlIdentity() {
}

unsigned char* getUnsignedCharFromString(QString str, int len) {
  unsigned char* result = new unsigned char[crypto_sign_SEEDBYTES];
  for (int i = 0; i < len; ++i) {
    result[i] = (unsigned char)str.at(i).toAscii();
  }
  return result;
}

/*
 * Generate a new SQRL identity.
 * Need to add **LOTS** of entropy here.
 */
bool SqrlIdentity::createIdentity() {
  qDebug() << "LOTS of entropy goes here";
  qDebug() << "Security warning: don't use this key for anything but testing!";

  qDebug() << "Currently the key is HARD-CODED!! Very bad!!";
  QString seed = "0123456789ABCDEF0123456789ABCDEF";
  this->key = getUnsignedCharFromString(seed, seed.length());

  QString folderName = QDir::homePath() + "/.sqrl";
  if (!QDir(folderName).exists())
    QDir().mkdir(folderName);

  QString fileName = "ident.txt";
  QFile file(folderName + "/" + fileName);

  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);
    for (unsigned int i = 0; i < crypto_sign_SEEDBYTES; ++i) {
      out << (char)this->key[i];
    }
    file.close();
  }
  else {
    qDebug() << "Error: couldn't open file for writing.";
  }

  return true;
}

/*
 * Load a SQRL identity from file.
 * In case of failure, return false, otherwise, return true.
 */
bool SqrlIdentity::loadIdentity() {
  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);

  if (file.size() == crypto_sign_SEEDBYTES) {
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      QString seed = in.readAll();
      this->key = getUnsignedCharFromString(seed, seed.length());
      file.close();

      return true;
    }
  }

  return false;
}

unsigned char* SqrlIdentity::getKey() {
  return this->key;
}

QString getStringFromUnsignedChar(unsigned char *str) {
  QString result = "";

  for (unsigned int i = 0; i < crypto_sign_SEEDBYTES; i++) {
    QChar c = str[i];
    result.append(c);
  }

  return result;
}

QString SqrlIdentity::getHexKey() {
  return getStringFromUnsignedChar(this->key);
}

QByteArray SqrlIdentity::makeDomainPrivateKey(QString domain) {
  QCA::Initializer init;

  QByteArray arg = domain.toLocal8Bit();
  QByteArray key((char*)this->getKey());

  if (!QCA::isSupported("hmac(sha256)")) {
    qDebug() << "hmac(sha256) is not supported!";
    return NULL;
  }
  else {
    QCA::MessageAuthenticationCode hmacObject("hmac(sha256)",
                                              QCA::SecureArray());

    QCA::SymmetricKey keyObject(key);

    hmacObject.setup(key);

    QCA::SecureArray converter(arg);

    hmacObject.update(converter);

    QCA::SecureArray result = hmacObject.final();

    return result.toByteArray();
  }
}

unsigned char* SqrlIdentity::signMessage(QString message,
                                         unsigned char* privateKey,
                                         unsigned char* publicKey) {
  /*
   * Debugging
   */
  printf("public key ");
  for (unsigned int i = 0; i < crypto_sign_PUBLICKEYBYTES; ++i) {
    printf("%02x", (unsigned char)publicKey[i]);
  }
  printf("\n");

  printf("private key ");
  for (unsigned int i = 0; i < crypto_sign_SECRETKEYBYTES; ++i) {
    printf("%02x", (unsigned char)privateKey[i]);
  }
  printf("\n");
  /*
   * End debugging
   */

  unsigned char* actualMessage = (unsigned char*)message.toAscii().constData();
  unsigned char sig[crypto_sign_BYTES];

  crypto_sign_detached(sig, NULL, actualMessage, message.length(), privateKey);

  if (crypto_sign_verify_detached(sig, actualMessage, message.length(),
                                  publicKey) != 0) {
    qDebug() << "Signing failed!";
    return NULL;
  }

  unsigned char* ret = sig;

  return ret;
}

QMap<QString,QString> SqrlIdentity::parseArgs(QString input) {
  QMap<QString,QString> output;
  QStringList list = input.split(CRLF,QString::SkipEmptyParts);

  for (int i = 0; i < list.size(); ++i) {
    QString line = list.at(i);

    // Split line based on first '='
    int j = line.indexOf('=');
    QString var = line.left(j);
    QString val = line.mid(j + 1);

    // Insert into map
    output.insert(var, val);
  }

  return output;
}

void SqrlIdentity::replyFinished(QNetworkReply* reply) {
  QVariant ret = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

  if (ret.type() != QVariant::Int) {
    qDebug() << "Return type is not an int. Something probably went wrong.";
    qDebug() << "ret: " << ret;
    return;
  }

  int retCode = ret.toInt();
  switch (retCode) {
    case 200:
      qDebug() << "Successful HTTP request. Continuing.";
      break;
    case 301:
      qDebug() << "Illegal SQRL query or bad URL... (Response code 301)";
      qDebug() << "Body is: " << reply->readAll();
      return;
    case 404:
      qDebug() << "Page not found! (Response code 404)";
      return;
    default:
      qDebug() << "I don't know about response code" << retCode;
      return;
  }

  QString rawReply = reply->readAll();

  QMap<QString,QString> parsedReply = this->parseArgs(rawReply);
  qDebug() << "parsed reply:" << parsedReply;

  int ver = 0;
  if (parsedReply.contains("ver")) {
    ver = parsedReply.take("ver").toInt();
    if (ver != 1) {
      qDebug() << "Error: unknown SQRL version:" << parsedReply.value("ver");
      return;
    }
  }
  else {
    qDebug() "Error: SQRL version not found!";
  }

  int tif = 0;
  if (parsedReply.contains("tif")) {
    tif = parsedReply.take("tif").toInt();
    qDebug() << "Raw TIF is" << tif;
  }
  else {
    qDebug() << "TIF not found!";
  }

  if ((tif & TIF_SQRL_FAILURE) != 0) {
    qDebug() << "SQRL failure (TIF 0x80). This is probably a bug.";
    //return;
  }

  if ((tif & TIF_COMMAND_FAILED) != 0)
    qDebug() << "Got TIF_COMMAND_FAILED.";
  if ((tif & TIF_IDK_MATCH) != 0)
    qDebug() << "Got TIF_IDK_MATCH.";
  if ((tif & TIF_PDK_MATCH) != 0)
    qDebug() << "Got TIF_PDK_MATCH.";
  if ((tif & TIF_IP_MATCH) != 0)
    qDebug() << "Got TIF_IP_MATCH.";
  if ((tif & TIF_STALE_NUT) != 0)
    qDebug() << "Got TIF_STALE_NUT.";
  if ((tif & TIF_ACC_ENABLED) != 0)
    qDebug() << "Got TIF_ACC_ENABLED.";
  if ((tif & TIF_ACC_LOGGED_IN) != 0)
    qDebug() << "Got TIF_ACC_LOGGED_IN.";
  if ((tif & TIF_TRANSIENT_FAILURE) != 0)
    qDebug() << "Got TIF_TRANSIENT_FAILURE.";

  QString sfn = "";
  if (parsedReply.contains("sfn")) {
    sfn = parsedReply.take("sfn");
    qDebug() << "Server is" << sfn;
  }
  else {
    qDebug() << "Server name not found!";
  }

  if (!parsedReply.isEmpty())
    qDebug() << "Found some extra arguments:" << parsedReply;
}

QString SqrlIdentity::base64url(QString input) {
  return this->trim(input.toAscii().toBase64());
}

QString SqrlIdentity::trim(QString input) {
  QString out = input;
  qDebug() << "  pre-trim:" << out;
  while (out.endsWith("="))
    out.chop(1);
  qDebug() << "  post-trim:" << out;

  return out;
}

bool SqrlIdentity::authenticate(QUrl url) {
  if (sodium_init() == -1) {
    qDebug() << "Error: sodium_init failed.";
    return false;
  }

  QByteArray domainSeed = this->makeDomainPrivateKey(url.host());

  // Prepare the seed
  unsigned char seed[crypto_sign_SEEDBYTES];
  memcpy(seed, domainSeed, crypto_sign_SEEDBYTES);

  // Prepare public and private keys
  unsigned char privateKey[crypto_sign_SECRETKEYBYTES];
  unsigned char publicKey[crypto_sign_PUBLICKEYBYTES];

  // Generate keys from seed
  crypto_sign_seed_keypair(publicKey, privateKey, seed);

  QString message = url.host() + url.path() + "?nut="
    + url.queryItemValue("nut");
  qDebug() << "message:" << message;

  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QUrl post("https://" + message);
  QNetworkRequest request(post);

  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");
  request.setRawHeader("User-Agent","SQRL/1");

  qDebug() << "idk:";
  QString idk = this->base64url(getStringFromUnsignedChar(publicKey));

  // Client arg
  QString client = "ver=1" + CRLF
    + "idk=" + idk + CRLF
    + "cmd=query" + CRLF;

  qDebug() << "client string:";
  client = this->base64url(client);

  // Server arg
  qDebug() << "server string: ";
  QString server = this->base64url(url.toString());

  message = client + server;

  unsigned char* signature = this->signMessage(message, privateKey, publicKey);
  qDebug() << "sig:";
  QString sig = this->base64url(getStringFromUnsignedChar(signature));

  QUrl params;
  params.addQueryItem("client",client);
  params.addQueryItem("server",server);
  params.addQueryItem("ids",sig);

  qDebug() << "params: " << params.encodedQuery();

  QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), (QObject*)this,
                   SLOT(replyFinished(QNetworkReply*)));

  manager->post(request, params.encodedQuery());

  return false;
}
