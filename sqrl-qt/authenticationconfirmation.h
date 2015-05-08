#ifndef AUTHENTICATIONCONFIRMATION_H
#define AUTHENTICATIONCONFIRMATION_H

#include <QWidget>

namespace Ui {
class AuthenticationConfirmation;
}

class AuthenticationConfirmation : public QWidget
{
  Q_OBJECT

 public:
  explicit AuthenticationConfirmation(QWidget *parent = 0);
  ~AuthenticationConfirmation();

 private:
  Ui::AuthenticationConfirmation *ui;
};

#endif // AUTHENTICATIONCONFIRMATION_H
