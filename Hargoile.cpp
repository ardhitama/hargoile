#include "Hargoile.h"

Hargoile::Hargoile(int &argc, char **argv) : QApplication(argc, argv)
{
    accountState = InvalidState;
    connectionState = InvalidState;
    gpsState = InvalidState;
    recorderState = InvalidState;

    const QString configFilename = QString("config.hgl");

    AccountLinkDlg aclDlg;
    aclDlg.showMaximized();
    aclDlg.exec();
}
