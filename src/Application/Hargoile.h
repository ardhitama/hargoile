#ifndef HARGOILE_H
#define HARGOILE_H

#include "../Exception/ExceptionAll.h"
#include "../Location/LocationAll.h"
#include "../../gui/qtm/WelcomeUI.h"

class Hargoile
{
public:
    Hargoile();

    virtual ~Hargoile();

    void initialize();
    void run();

    // UIs
    void openWelcomeUI();

    void errorNotification();

    // Location recording
    int startRouteRecording();
    int pauseRouteRecording();
    int stopRouteRecording();

    // Route Storage
    int loadRoute(int routeId);
    int saveRoute(); //returns route id, zero if failed

    int downloadRoute(); //returns route id, zero if failed
    int uploadRoute(int routeId);

    // Account linking
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
    LocationRecorder *locRecorder;
};

#endif // HARGOILE_H
