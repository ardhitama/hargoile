#include "Hargoile.h"

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
    welcomeUI.setMaximized();
    welcomeUI.show();
}

void Hargoile::openRecorderUI()
{
    recorderUI->setMaximized();
    recorderUI->show();
}

void Hargoile::errorNotification()
{
}

void Hargoile::run()
{
    try
    {
        //openWelcomeUI();
        locRecorder = new LocationRecorder();
        recorderUI = new RecorderUI();
        openRecorderUI();

    } catch(Exception &ex)
    {
        //
    }
}

int Hargoile::startRouteRecording()
{
    locRecorder->start();
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

void Hargoile::addNewPosition(const String &msg)
{
    recorderUI->appendPositionListView(msg);
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
