#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include <QDialog>
#include "../UIAbstract.h"

namespace Ui {
class WelcomeUI;
}

class WelcomeUI : public QDialog, virtual public UIAbstract
{
    Q_OBJECT
public:
    explicit WelcomeUI(QWidget *parent = 0);
    ~WelcomeUI();

    void toLinkedState();
    void toNotLinkedState();

    void show();
    void hide();
    void close();
    void setMinimized();
    void setMaximized();
    void toFront();

private:
    Ui::WelcomeUI *ui;
    QPushButton *quitBtn, *startBtn, *linkBtn, *menuBtn;

private slots:
    void recordBtnClicked();
    void linkBtnClicked();
    void quitBtnClicked();
    void menuBtnClicked();
};

#endif // WELCOMEUI_H
