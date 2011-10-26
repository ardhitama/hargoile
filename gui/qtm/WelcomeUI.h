#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include <QDialog>
#include "../UIAbstract.h"

namespace Ui {
class WelcomeUI;
}

class WelcomeUI : public QDialog, protected UIAbstract
{
    Q_OBJECT
public:
    explicit WelcomeUI(QWidget *parent = 0);
    ~WelcomeUI();

    void show();
    void hide();
    void close();
    void destroy();
    void setMinimized();
    void setMaximized();

private:
    Ui::WelcomeUI *ui;
};

#endif // WELCOMEUI_H
