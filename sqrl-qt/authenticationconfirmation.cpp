#include "authenticationconfirmation.h"
#include "ui_authenticationconfirmation.h"

AuthenticationConfirmation::AuthenticationConfirmation(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AuthenticationConfirmation) {
  ui->setupUi(this);
}

AuthenticationConfirmation::~AuthenticationConfirmation() {
  delete ui;
}
