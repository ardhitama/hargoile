#ifndef ROUTECONFIGUI_H
#define ROUTECONFIGUI_H

#include <QDialog>
#include "../UIAbstract.h"

namespace Ui {
    class RouteConfigUI;
}

class RouteConfigUI : public QDialog, virtual public UIAbstract
{
    Q_OBJECT

public:
    explicit RouteConfigUI(QWidget *parent = 0);
    ~RouteConfigUI();

    void show();
    void hide();
    void close();
    void setMinimized();
    void setMaximized();
    void toFront();

private:
    Ui::RouteConfigUI *ui;
    QPushButton *continueBtn, *backBtn;

private slots:
    void continueBtnClicked();
    void backBtnClicked();
};

#endif // ROUTECONFIGUI_H
