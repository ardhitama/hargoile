#ifndef HARGOILE_H
#define HARGOILE_H

#include <queue>
#include "../../libs/boost/shared_ptr.hpp"
#include "../../libs/boost/make_shared.hpp"

#include "../Exception/ExceptionAll.h"
#include "../Location/LocationAll.h"
#include "../../gui/UIAll.h"
#include "../Network/NetworkAll.h"
#include "../Technique/Singleton.h"
#include "../Utility/UtilityAll.h"

#include "Storage.h"
#include "Route.h"

class Hargoile : public Singleton<Hargoile>
{
public:
    Hargoile();
    virtual ~Hargoile();

    void init();
    void run();
    void destroy();

    std::queue<int>& getUIQueue();

    // UIs
    void createWelcomeUI();
    void createRecorderUI();
    void openMenuUI(UIAbstract *parentUI);
    void createRouteConfigUI();

    void errorNotification();

    // Location recording
    void createNewRoute();
    void startRouteRecording();
    void pauseRouteRecording();
    void stopRouteRecording();
    void addNewPosition(GeoPoint& gp);

    // Route Storage
    int loadRoute(int routeId);
    int saveRoute(); //returns route id, zero if failed

    Route getReducedCurrentRoute();
    bool uploadRoute(Route& route);
    int downloadRoute();
    Route& getCurrentRoute();
    double getCurrentDPTolerance();
    void setCurrentDPTolerance(double tolerance);

    // Account linking
    void saveAuthentication(String email, String password);
    bool isAccountLinked();
    bool linkAccount(String email, String password);
    void unlinkAccount();

    void onLinkAccount(VariantMap& var);

    void showAccountDialog();
    void showRecorderDialog();
    void showManagerDialog();
    void showRouteDialog();

    void closeAllDialog();

    void restartAllThread();
    void pauseAllThread();
    void stopAllThread();

    enum {UI_WELCOME, UI_RECORDER, UI_MENU, UI_ROUTECONFIG};
private:
    boost::shared_ptr<LocationRecorder> locRecorder;
    boost::shared_ptr<Http> http;

    boost::shared_ptr<WelcomeUI> welcomeUI;
    boost::shared_ptr<RecorderUI> recorderUI;
    boost::shared_ptr<MenuUI> menuUI;
    boost::shared_ptr<RouteConfigUI> routeConfigUI;

    bool isRecording;
    bool isRunning;
    Route currentRoute;

    std::queue<int> uiQueue;
};

#endif // HARGOILE_H
