#ifndef IDENTITYCREATIONWINDOWPAGE1_H
#define IDENTITYCREATIONWINDOWPAGE1_H

#include <QWidget>

namespace Ui {
  class IdentityCreationWindowPage1;
}

class IdentityCreationWindowPage1 : public QWidget {
  Q_OBJECT

 public:
  explicit IdentityCreationWindowPage1(QWidget *parent = 0);
  ~IdentityCreationWindowPage1();

 private:
    Ui::IdentityCreationWindowPage1 *ui;
};

#endif
