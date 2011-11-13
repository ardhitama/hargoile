#include "Hargoile.h"
#include "MovementSimulator.h"
/*
  Event driven application
*/

Hargoile::Hargoile()
{
    initialize();

    //
}

Hargoile::~Hargoile()
{
}

void Hargoile::initialize()
{

    /*StateManager::getInstance().switchState(StateManager::Init);

    if(Config::getInstance().getToken() == "") // account token is empty
    {
        StateManager::getInstance().switchState(StateManager::LingkingAccount);
        showAccountDialog();
    }*/

    // start recording
    try
    {
        http = boost::make_shared<Http>();

        std::srand(hgl::rangedRand(777, 9999));

        isRecording = false;
        //posRecorder = boost::shared_ptr<PositionRecorderImpl>(new PositionRecorderImpl());
        //posRecorder->start();
    } catch(Exception &ex)
    {
        //
    }
}

void Hargoile::openWelcomeUI()
{
    welcomeUI->setMaximized();
    welcomeUI->show();
}

void Hargoile::openRecorderUI()
{
    recorderUI->setMaximized();
    recorderUI->show();
}

void Hargoile::openMenuUI()
{
    menuUI->setMaximized();
    menuUI->show();
}

void Hargoile::errorNotification()
{
}

void Hargoile::run()
{
    try
    {
        locRecorder = boost::make_shared<LocationRecorder>();
        welcomeUI = boost::make_shared<WelcomeUI>();
        recorderUI = boost::make_shared<RecorderUI>();
        menuUI = boost::make_shared<MenuUI>();

        openWelcomeUI();

    } catch(Exception &ex)
    {
        //
    }
}

void Hargoile::destroy()
{
    exit(0);
}

void Hargoile::startRouteRecording()
{
    isRecording = true;
    locRecorder->start();
    currentRoute = Route();
    recorderUI->toRecordingState();
}

void Hargoile::pauseRouteRecording()
{
    locRecorder->stop();
    recorderUI->toPausedState();
}

void Hargoile::stopRouteRecording()
{
    isRecording = false;
    locRecorder->stop();
    recorderUI->toStoppedState();

    //    currentRoute = simulateMovement("rute", 1, 500, 5);
    //    uploadCurrentRoute();
    //    currentRoute.simplify(1);

    //    boost::uuids::random_generator randGen;
    //    boost::uuids::uuid uuid = randGen();
    //    currentRoute.setUUID(boost::uuids::to_string(uuid));

    //    currentRoute.setName("rute-reduced");
    //    uploadCurrentRoute();
}

void Hargoile::addNewPosition(GeoPoint& gp)
{
    String strLoc;
    strLoc << gp.getLongitude() << ", " << gp.getLatitude();

    currentRoute.addPoint(gp);

    recorderUI->appendPositionListView(strLoc);
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

Route Hargoile::getReducedCurrentRoute()
{
    Route route = currentRoute;
    route.generateUUID();
    route.setName(route.getName() << " - reduced");
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
            jsGp.push_back(JSONNode("", gp.getLatitude()));
            jsGp.push_back(JSONNode("", gp.getLongitude()));
            jsGp.push_back(JSONNode("", gp.getAltitude()));
            jsGp.push_back(JSONNode("", gp.getTime()));
            jsGp.push_back(JSONNode("", gp.getHSpeed()));
            jsGp.push_back(JSONNode("", gp.getVSpeed()));
            jsGp.push_back(JSONNode("", gp.getHAccuracy()));
            jsGp.push_back(JSONNode("", gp.getVAccuracy()));

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
        return false;
    }

    return true;
}

void Hargoile::unlinkAccount()
{
    Storage::getInstance().saveAuth("", "");
    welcomeUI->toNotLinkedState();
    if(isRecording == true)
    {
        stopRouteRecording();
        recorderUI->close();
    }
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
