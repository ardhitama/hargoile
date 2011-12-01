#include "Hargoile.h"
#include "MovementSimulator.h"
/*
  Event driven application
*/

Hargoile::Hargoile()
{
    isRecording = false;
    isRunning = true;
}

Hargoile::~Hargoile()
{
}

void Hargoile::createWelcomeUI()
{
    if(isAccountLinked())
        welcomeUI->toLinkedState();
    else
        welcomeUI->toNotLinkedState();

    welcomeUI->setMaximized();
    welcomeUI->show();
}

void Hargoile::createRecorderUI()
{
    recorderUI->setMaximized();
    recorderUI->show();
}

void Hargoile::openMenuUI(UIAbstract *parentUI, int menuType = 0)
{
    menuUI->setParentUI(parentUI);
    menuUI->setMenuType(menuType);
    menuUI->setMaximized();
    menuUI->toFront();
    menuUI->show();
}

void Hargoile::createRouteConfigUI()
{
    routeConfigUI->setMaximized();
    routeConfigUI->show();
}

void Hargoile::errorNotification()
{
}

void Hargoile::init()
{
    try
    {
        std::srand(hgl::rangedRand(777, 9999));

        http = boost::make_shared<Http>();
        locRecorder = boost::make_shared<LocationRecorder>();

        welcomeUI = boost::make_shared<WelcomeUI>();
        recorderUI = boost::make_shared<RecorderUI>();
        menuUI = boost::make_shared<MenuUI>();
        routeConfigUI = boost::make_shared<RouteConfigUI>();

        uiQueue.push(UI_WELCOME);

    } catch(Exception &ex)
    {
        //
    }
}

void Hargoile::run()
{
    int currentUI = -1;

    locRecorder->start();
    locRecorder->setUpdateInterval(15000);

    while(!uiQueue.empty())
    {
        currentUI = uiQueue.front();
        uiQueue.pop();

        switch(currentUI)
        {
        case UI_WELCOME:
            createWelcomeUI(); // createWelcomeUI is a blockin operation
            break;
        case UI_RECORDER:
            createRecorderUI();
            stopRouteRecording();
            break;
        case UI_ROUTECONFIG:
            createRouteConfigUI();
            break;
        }
    }
    locRecorder->stop();
}

void Hargoile::destroy()
{
    exit(0);
}

std::queue<int>& Hargoile::getUIQueue()
{
    return uiQueue;
}

void Hargoile::createNewRoute()
{
    currentRoute = Route();
}

void Hargoile::startRouteRecording()
{
    isRecording = true;
    //locRecorder->start();
    locRecorder->setUpdateInterval(1000);
    locRecorder->forceUpdate();
    recorderUI->toRecordingState();
}

void Hargoile::pauseRouteRecording()
{
    locRecorder->setUpdateInterval(15000);
    recorderUI->toPausedState();
}

void Hargoile::stopRouteRecording()
{
    if(isRecording)
    {
        isRecording = false;
        //locRecorder->stop();
        locRecorder->setUpdateInterval(15000);
        recorderUI->toStoppedState();
    }
}

void Hargoile::addNewPosition(GeoPoint& gp)
{
    String strLoc;
    if(isRecording)
    {
        strLoc << gp.getLatitude() << ", " << gp.getLongitude();

        currentRoute.addPoint(gp);

        recorderUI->appendPositionListView(strLoc);
    }
}

int Hargoile::loadRoute(int routeId)
{
    return 0;
}

int Hargoile::saveRoute()
{
    return 0;
}

int Hargoile::downloadRoute()
{
    return 0;
}

Route& Hargoile::getCurrentRoute()
{
    return currentRoute;
}

double Hargoile::getCurrentDPTolerance()
{
    return Storage::getInstance().getDPTolerance();
}

void Hargoile::setCurrentDPTolerance(double tolerance)
{
    Storage::getInstance().setDPTolerance(tolerance);
}

int Hargoile::getCurrentAccuracyTolerance()
{
    return Storage::getInstance().getAccuracyTolerance();
}

void Hargoile::setCurrentAccuracyTolerance(int tolerance)
{
    Storage::getInstance().setAccuracyTolerance(tolerance);
}

Route Hargoile::getReducedCurrentRoute()
{
    Route route = currentRoute;
    route.generateUUID();
    route.setName(route.getName() << " [" << hgl::round(Storage::getInstance().getAccuracyTolerance(), 1) << "][" << hgl::round(Storage::getInstance().getDPTolerance(), 1) << "]");
    route.simplify(Storage::getInstance().getDPTolerance());
    return route;
}

bool Hargoile::uploadRoute(Route& route)
{
    try
    {
        if(Storage::getInstance().getExchangeUrl().length() == 0)
        {
            LogOut::error("Application config error. (URL is invalid)");
            return false;
        }
        if(isAccountLinked() == false)
        {
            LogOut::error("You must link your account first.");
            return false;
        }

        if(route.getGeoPointData().size() == 0)
        {
            LogOut::error("Can't process upload, route is empty.");
            return false;
        }

        HttpRequest req(Storage::getInstance().getExchangeUrl());
        req.addFormField("input-email", Storage::getInstance().getEmail());
        req.addFormField("input-password", Storage::getInstance().getPassword());

        JSONNode jsRoute(JSON_NODE), jsPoints(JSON_ARRAY);
        jsRoute.push_back(JSONNode("uuid", route.getUUID().data()));
        jsRoute.push_back(JSONNode("name", route.getName().data()));
        jsPoints.set_name("points");

        for(unsigned int i=0; i<route.getGeoPointData().size(); ++i)
        {
            GeoPoint gp = route.getGeoPointData().at(i);
            JSONNode jsGp(JSON_ARRAY);
            jsGp.push_back(JSONNode("", String(gp.getLatitude())));
            jsGp.push_back(JSONNode("", String(gp.getLongitude())));
            jsGp.push_back(JSONNode("", String(gp.getAltitude())));
            jsGp.push_back(JSONNode("", String(gp.getTime())));
            jsGp.push_back(JSONNode("", String(gp.getHSpeed())));
            jsGp.push_back(JSONNode("", String(gp.getVSpeed())));
            jsGp.push_back(JSONNode("", String(gp.getHAccuracy())));
            jsGp.push_back(JSONNode("", String(gp.getVAccuracy())));

            jsPoints.push_back(jsGp);
        }

        jsRoute.push_back(jsPoints);
        String jsData = jsRoute.write_formatted();
        req.addFormField("input-route", jsData);

        VariantMap postResponse;
        http->post(req, postResponse);

    } catch(Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
        if(RetryUI::show("Route upload is failed, retry?"))
            return uploadRoute(route);
        else
            return false;
    }

    return true;
}

void Hargoile::saveAuthentication(String email, String password)
{
    Storage::getInstance().saveAuth(email, password);
}

bool Hargoile::isAccountLinked()
{
    if(Storage::getInstance().getEmail().length() == 0)
        return false;
    if(Storage::getInstance().getPassword().length() == 0)
        return false;

    return true;
}

bool Hargoile::linkAccount(String email, String password)
{
    try
    {
        if(email.length() == 0 || password.length() == 0)
        {
            LogOut::error("Email and/or password field is empty");
            return false;
        }

        HttpRequest req(Storage::getInstance().getLinkUrl());
        req.addFormField("input-email", email);
        req.addFormField("input-password", password);

        VariantMap message;
        message.add("email", email);
        message.add("password", password);


        if(http->post(req, message) == true)
        {
            onLinkAccount(message);
        }

    } catch(Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");

        if(RetryUI::show("Account linking is failed, retry?"))
            return linkAccount(email, password);
        else
            return false;
    }

    return true;
}

void Hargoile::unlinkAccount()
{
    Storage::getInstance().saveAuth("", "");
}

void Hargoile::onLinkAccount(VariantMap& varMap)
{
    try
    {
        Json json;
        json.parse(varMap.get("http_response").toString());

        if(json.toBool("response") == true)
        {
            welcomeUI->toLinkedState();
            Storage::getInstance().saveAuth(varMap.get("email").toString(), varMap.get("password").toString());
        }
        else
            LogOut::error("Email and/or Password is wrong.");
    }
    catch(std::invalid_argument)
    {
        LogOut::error("Account linking is failed because remote server gives unexpected respond.");
    }
    catch(Exception& ex)
    {
        LogOut::error("Unexcepted error occured while linking your account.");
    }
}


void Hargoile::showAccountDialog()
{
}

void Hargoile::showRecorderDialog()
{
}

void Hargoile::showManagerDialog()
{
}

void Hargoile::showRouteDialog()
{
}

void Hargoile::closeAllDialog()
{
}
