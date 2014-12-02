#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identitycreationwindowpage1.cpp"
#include <QString>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QString filename = QDir::homePath() + "/.sqrl/ident.txt";
  QFile file(filename);
  QString key;

  if (file.open(QIODevice::ReadOnly)) {
      QTextStream stream(&file);
      key = stream.readLine();
  }

  if (key.length() == 64) {
    ui->label_2->setText(key);
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
