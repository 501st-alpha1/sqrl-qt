#include "identitycreationwindowpage1.h"
#include "ui_identitycreationwindowpage1.h"

IdentityCreationWindowPage1::IdentityCreationWindowPage1(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::IdentityCreationWindowPage1) {
  ui->setupUi(this);
}

IdentityCreationWindowPage1::~IdentityCreationWindowPage1() {
  delete ui;
}
