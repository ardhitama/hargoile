#ifndef STORAGE_H
#define STORAGE_H

#include "config.h"
#include "../Database/DatabaseAll.h"
#include "../Utility/String.h"
#include "../Technique/Singleton.h"
#include "Route.h"
#include <map>
#include <algorithm>

class Storage : public Singleton<Storage>
{
public:
    Storage();
    void setAccessToken(String& strToken);
    String getAccessToken();
    void addRoute(Route& route);
    Route getRoute(String& routeUUID);
    void deleteRoute(String& routeUUID);
    std::map<String, String> listAllRoutes();

private:
    Database db;
};

#endif // STORAGE_H
