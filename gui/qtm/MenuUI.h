#ifndef MENUUI_H
#define MENUUI_H

#include <QDialog>
#include "../UIAbstract.h"

namespace Ui {
    class MenuUI;
}

class MenuUI : public QDialog, public UIAbstract
{
    Q_OBJECT

public:
    MenuUI(QWidget *parent = 0);
    ~MenuUI();

    void show();
    void hide();
    void close();
    void setMinimized();
    void setMaximized();
    void toFront();

private:
    Ui::MenuUI *ui;
    QPushButton *backBtn;

private slots:
    void backBtnClicked(); 
    void on_routeUploadBtn_clicked();
    void on_reducedRouteUploadBtn_clicked();
    void on_quitBtn_clicked();
    void on_unlinkBtn_clicked();
    void on_newRouteBtn_clicked();
};

#endif // MENUUI_H
