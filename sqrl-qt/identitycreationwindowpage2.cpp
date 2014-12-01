#include "identitycreationwindowpage2.h"
#include "ui_identitycreationwindowpage2.h"

IdentityCreationWindowPage2::IdentityCreationWindowPage2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdentityCreationWindowPage2) {
  ui->setupUi(this);
}

IdentityCreationWindowPage2::~IdentityCreationWindowPage2() {
  delete ui;
}

void IdentityCreationWindowPage2::on_pushButton_clicked() {
  this->close();
}

void IdentityCreationWindowPage2::on_pushButton_2_clicked() {

}
