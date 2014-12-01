#ifndef IDENTITYCREATIONWINDOWPAGE2_H
#define IDENTITYCREATIONWINDOWPAGE2_H

#include <QWidget>

namespace Ui {
class IdentityCreationWindowPage2;
}

class IdentityCreationWindowPage2 : public QWidget
{
    Q_OBJECT

public:
    explicit IdentityCreationWindowPage2(QWidget *parent = 0);
    ~IdentityCreationWindowPage2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::IdentityCreationWindowPage2 *ui;
};

#endif // IDENTITYCREATIONWINDOWPAGE2_H
