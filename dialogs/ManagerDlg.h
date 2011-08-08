#ifndef MANAGERDLG_H
#define MANAGERDLG_H

#include <QDialog>

namespace Ui {
    class ManagerDlg;
}

class ManagerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ManagerDlg(QWidget *parent = 0);
    ~ManagerDlg();

private:
    Ui::ManagerDlg *ui;
};

#endif // MANAGERDLG_H
