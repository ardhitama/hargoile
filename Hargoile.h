#ifndef HARGOILE_H
#define HARGOILE_H

#include "stdafx.h"
#include "AccountLinkDlg.h"

class Hargoile : public QApplication
{
private:
    enum { LinkedState, NoConnectionState, RecordingRouteState, InvalidState };
    int accountState, connectionState, gpsState, recorderState;
    const QString configFilename;
public:
    Hargoile(int &argc, char **argv);
    void loadConfig();
    void saveConfig();
    bool isAccountLinked();
};

#endif // HARGOILE_H
