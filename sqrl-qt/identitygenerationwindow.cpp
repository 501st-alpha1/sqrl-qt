#include "identitygenerationwindow.h"
#include "ui_identitygenerationwindow.h"

IdentityGenerationWindow::IdentityGenerationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdentityGenerationWindow)
{
    ui->setupUi(this);
}

IdentityGenerationWindow::~IdentityGenerationWindow()
{
    delete ui;
}
