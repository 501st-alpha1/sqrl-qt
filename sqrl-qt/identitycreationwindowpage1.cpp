#include "identitycreationwindowpage1.h"
#include "ui_identitycreationwindowpage1.h"
//#include "identitycreationwindowpage2.h"

IdentityCreationWindowPage1::IdentityCreationWindowPage1(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::IdentityCreationWindowPage1) {
  ui->setupUi(this);
}

IdentityCreationWindowPage1::~IdentityCreationWindowPage1() {
  delete ui;
}

void IdentityCreationWindowPage1::on_pushButton_clicked() {
  this->close();
}

void IdentityCreationWindowPage1::on_pushButton_2_clicked() {
  this->close();
  SqrlIdentity* ident = new SqrlIdentity;
  ident->createIdentity();
  /*
   * FIXME: implement the rest of the wizard
   * IdentityCreationWindowPage2 *page2 = new IdentityCreationWindowPage2();
   * page2->show();
   */
}
