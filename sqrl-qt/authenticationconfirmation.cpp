#include "authenticationconfirmation.h"
#include "ui_authenticationconfirmation.h"
#include <QDebug>

AuthenticationConfirmation::AuthenticationConfirmation(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AuthenticationConfirmation) {
  ui->setupUi(this);
}

void AuthenticationConfirmation::setAuthenticator(SqrlAuthenticator* auth) {
  this->auth = auth;
  ui->label_2->setText(auth->sfn);
}

AuthenticationConfirmation::~AuthenticationConfirmation() {
  delete ui;
}

void AuthenticationConfirmation::on_pushButton_clicked() {
  qDebug() << "Pressed No";
  return;
}

void AuthenticationConfirmation::on_pushButton_3_clicked() {
  qDebug() << "Pressed Options";
  return;
}

void AuthenticationConfirmation::on_pushButton_2_clicked() {
  qDebug() << "Pressed Yes";

  QUrl identUrl(auth->getNextSqrlUrl());
  auth->ident(identUrl);

  return;
}
