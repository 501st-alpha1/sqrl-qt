#include "authenticationconfirmation.h"
#include "ui_authenticationconfirmation.h"

AuthenticationConfirmation::AuthenticationConfirmation(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AuthenticationConfirmation) {
  ui->setupUi(this);
}

void AuthenticationConfirmation::setSFN(QString sfn) {
  this->sfn = sfn;
  ui->label_2->setText(sfn);
}

AuthenticationConfirmation::~AuthenticationConfirmation() {
  delete ui;
}
