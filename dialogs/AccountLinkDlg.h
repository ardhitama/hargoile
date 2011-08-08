#ifndef ACCOUNTLINKDLG_H
#define ACCOUNTLINKDLG_H

#include "stdafx.h"

namespace Ui {
    class AccountLinkDlg;
}

class AccountLinkDlg : public QDialog
{
    Q_OBJECT

public:

    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    AccountLinkDlg(QWidget *parent = 0);

    void setOrientation(ScreenOrientation orientation);
    void showExpanded();

    virtual ~AccountLinkDlg();
private:
    Ui::AccountLinkDlg *ui;
    QPointer<QAction> linkAct, quitAct;
private slots:
    void doLink();
    void exitApp();
};

#endif // ACCOUNTLINKDLG_H
