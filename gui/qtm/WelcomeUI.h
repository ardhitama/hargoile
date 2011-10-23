#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include <QDialog>

namespace Ui {
    class WelcomeUI;
}

class WelcomeUI : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeUI(QWidget *parent = 0);
    ~WelcomeUI();

private:
    Ui::WelcomeUI *ui;
};

#endif // WELCOMEUI_H
