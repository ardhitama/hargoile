#include "Hargoile.h"

Hargoile::Hargoile()
{
    initialize();
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
        posRecorder = boost::shared_ptr<PositionRecorderImpl>(new PositionRecorderImpl());
        posRecorder->start();
    } catch(Exception &ex)
    {
        //
    }
}

int Hargoile::startRouteRecording()
{
}

int Hargoile::pauseRouteRecording()
{
}

int Hargoile::stopRouteRecording()
{
}

int Hargoile::loadRoute(int routeId)
{
}

int Hargoile::saveRoute()
{
}

int Hargoile::downloadRoute()
{
}

int Hargoile::uploadRoute(int routeId)
{
}

int Hargoile::linkAccount()
{
}

int Hargoile::unlinkAccount()
{
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
