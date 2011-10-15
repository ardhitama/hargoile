#ifndef HARGOILE_H
#define HARGOILE_H

#include "stdafx.h"
#include "StateManager.h"
#include "Storage.h"
#include "Config.h"
#include "Location/PositionRecorder.h"
#ifdef QT_MOBILITY
#include "Location/qt-mobility/PositionRecorderImpl.h"
#endif // QT_MOBILITY

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
private:
    boost::shared_ptr<PositionRecorder> posRecorder;
};

#endif // HARGOILE_H
