#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identitycreationwindowpage1.cpp"
#include <QString>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QDebug>
#include "sqrlidentity.h"
#include "sqrlauthenticator.h"
#include "authenticationconfirmation.h"
#include "sqrlsettings.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ident = new SqrlIdentity;
  if (ident->loadIdentity()) {
    ui->label_2->setText(QString(ident->getKey()));
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

void MainWindow::on_pushButton_2_clicked() {
  SqrlAuthenticator* auth = new SqrlAuthenticator(this->ident);
  auth->query(ui->lineEdit_3->text());

  // Hax!!
  QTime dieTime = QTime::currentTime().addSecs(5);
  while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

  if (!auth->querySuccess) {
    qDebug() << "The 'query' command was not successful. Either something went"
             << "wrong, or the request timed out.";
    return;
  }

  AuthenticationConfirmation* confirm = new AuthenticationConfirmation;
  confirm->setAuthenticator(auth);
  confirm->show();
}
