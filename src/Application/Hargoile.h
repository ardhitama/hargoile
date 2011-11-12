#ifndef HARGOILE_H
#define HARGOILE_H

#include "../../libs/boost/shared_ptr.hpp"
#include "../../libs/boost/make_shared.hpp"

#include "../Exception/ExceptionAll.h"
#include "../Location/LocationAll.h"
#include "../../gui/UIAll.h"
#include "../Network/NetworkAll.h"
#include "../Technique/Singleton.h"
#include "../Utility/UtilityAll.h"
#include "../Application.h"

#include "Storage.h"
#include "Route.h"

class Hargoile : public Application, public Singleton<Hargoile>
{
public:
    Hargoile();
    virtual ~Hargoile();

    void run();
    void initialize();
    void destroy();

    // UIs
    void openWelcomeUI();
    void openRecorderUI();
    void openMenuUI();

    void errorNotification();

    // Location recording
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

private:
    boost::shared_ptr<LocationRecorder> locRecorder;
    boost::shared_ptr<WelcomeUI> welcomeUI;
    boost::shared_ptr<RecorderUI> recorderUI;
    boost::shared_ptr<MenuUI> menuUI;
    boost::shared_ptr<Http> http;

    bool isRecording;
    Route currentRoute;


};

#endif // HARGOILE_H
