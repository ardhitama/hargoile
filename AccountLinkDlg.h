#ifndef ACCOUNTLINKDLG_H
#define ACCOUNTLINKDLG_H

#include <QDialog>
#include <QAction>
#include "stdafx.h"

namespace Ui {
    class AccountLinkDlg;
}

class AccountLinkDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AccountLinkDlg(QWidget *parent = 0);
    ~AccountLinkDlg();

private:
    Ui::AccountLinkDlg *ui;
    QPointer<QAction> linkAct, quitAct;

private slots:
    void doLink();
    void exitApp();
};

#endif // ACCOUNTLINKDLG_H
