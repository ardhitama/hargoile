#ifndef HARGOILE_H
#define HARGOILE_H

#include "StateManager.h"
#include "Storage.h"
#include "Config.h"
#include "stdafx.h"

class Hargoile
{
public:
    Hargoile();
    virtual ~Hargoile();

    void initialize();

    int startRouteRecording();
    int pauseRouteRecording();
    int stopRouteRecording();

    int loadRoute(int routeId);
    int saveRoute(); //returns route id, zero if failed

    int downloadRoute(); //returns route id, zero if failed
    int uploadRoute(int routeId);

    int linkAccount();
    int unlinkAccount();

    void showAccountDialog();
    void showRecorderDialog();
    void showManagerDialog();
    void showRouteDialog();

    void closeAllDialog();

    void restartAllThread();
    void pauseAllThread();
    void stopAllThread();
};

#endif // HARGOILE_H
