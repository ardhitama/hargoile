#ifndef MAINWINDOWUI_H
#define MAINWINDOWUI_H

#include <QMainWindow>
#include "../UIAbstract.h"
#include "../UIAll.h"

namespace Ui {
    class MainWindowUI;
}

class MainWindowUI : public QMainWindow, virtual public UIAbstract
{
    Q_OBJECT
public:
    explicit MainWindowUI(QWidget *parent = 0);
    virtual ~MainWindowUI();

    void show();
    void hide();
    void close();
    void setMinimized();
    void setMaximized();
    void toFront();

    void closeEvent(QCloseEvent *event);

private:
    std::unique_ptr<Ui::MainWindowUI> ui;
};

#endif // MAINWINDOWUI_H
