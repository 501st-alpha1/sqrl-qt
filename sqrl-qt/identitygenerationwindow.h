#ifndef IDENTITYGENERATIONWINDOW_H
#define IDENTITYGENERATIONWINDOW_H

#include <QWidget>

namespace Ui {
class IdentityGenerationWindow;
}

class IdentityGenerationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IdentityGenerationWindow(QWidget *parent = 0);
    ~IdentityGenerationWindow();

private:
    Ui::IdentityGenerationWindow *ui;
};

#endif // IDENTITYGENERATIONWINDOW_H
