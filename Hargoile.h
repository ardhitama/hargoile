#ifndef HARGOILE_H
#define HARGOILE_H

#include "stdafx.h"
#include "AccountLinkDlg.h"

class Hargoile : public QApplication
{
public:
    Hargoile(int &argc, char **argv);
    virtual ~Hargoile();

    void loadConfig();
    void saveConfig();
    bool isAccountLinked();

private:
    enum HargoileState { LinkedState, NoConnectionState, RecordingRouteState, InvalidState };
    int accountState, connectionState, gpsState, recorderState;
    const QString configFilename;
};

#endif // HARGOILE_H
