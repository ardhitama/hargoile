#include "Hargoile.h"

/*
  Event driven application
*/

Hargoile::Hargoile()
{
    locRecorder = new LocationRecorder();
    //initialize();
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
        //posRecorder = boost::shared_ptr<PositionRecorderImpl>(new PositionRecorderImpl());
        //posRecorder->start();
    } catch(Exception &ex)
    {
        //
    }
}

void Hargoile::openWelcomeUI()
{
    WelcomeUI welcomeUI;
    welcomeUI.showMaximized();
    welcomeUI.exec();
}

void Hargoile::errorNotification()
{
}

void Hargoile::run()
{
    try
    {
        openWelcomeUI();
    } catch(Exception &ex)
    {
        //
    }
}

int Hargoile::startRouteRecording()
{
    return 0;
}

int Hargoile::pauseRouteRecording()
{
    return 0;
}

int Hargoile::stopRouteRecording()
{
    return 0;
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

int Hargoile::uploadRoute(int routeId)
{
    return 0;
}

int Hargoile::linkAccount()
{
    return 0;
}

int Hargoile::unlinkAccount()
{
    return 0;
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
