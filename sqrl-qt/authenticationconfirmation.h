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
  void setSFN(QString sfn);
  void on_pushButton_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_2_clicked();

 private:
  Ui::AuthenticationConfirmation *ui;
  QString sfn;
};

#endif // AUTHENTICATIONCONFIRMATION_H
