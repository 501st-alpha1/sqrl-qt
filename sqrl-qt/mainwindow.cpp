#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identitycreationwindowpage1.cpp"
#include <QString>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  SqrlIdentity* ident = new SqrlIdentity;
  if (ident->loadIdentity()) {
    ui->label_2->setText(ident->getHexKey());
  }
  else {
    ui->label_2->setText("No key found, or key is invalid");
  }
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  IdentityCreationWindowPage1 *identWiz = new IdentityCreationWindowPage1;
  identWiz->show();
}
