#ifndef MENUUI_H
#define MENUUI_H

#include <QDialog>

namespace Ui {
    class MenuUI;
}

class MenuUI : public QDialog
{
    Q_OBJECT

public:
    explicit MenuUI(QWidget *parent = 0);
    ~MenuUI();

private:
    Ui::MenuUI *ui;
};

#endif // MENUUI_H
