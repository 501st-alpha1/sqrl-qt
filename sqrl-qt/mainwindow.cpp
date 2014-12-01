#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identitycreationwindowpage1.cpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  IdentityCreationWindowPage1 *identWiz = new IdentityCreationWindowPage1;
  identWiz->show();
}
