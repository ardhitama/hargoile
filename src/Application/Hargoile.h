#ifndef HARGOILE_H
#define HARGOILE_H

#include "../../libs/boost/shared_ptr.hpp"
#include "../Exception/ExceptionAll.h"
#include "../Location/LocationAll.h"
#include "../../gui/UIAll.h"
#include "../Technique/Singleton.h"

class Hargoile : public Singleton<Hargoile>
{
public:
    Hargoile();
    virtual ~Hargoile();

    void initialize();
    void run();

    // UIs
    void openWelcomeUI();
    void openRecorderUI();

    void errorNotification();

    // Location recording
    int startRouteRecording();
    int pauseRouteRecording();
    int stopRouteRecording();
    void addNewPosition(const String &msg);

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
    RecorderUI *recorderUI;
};

#endif // HARGOILE_H
