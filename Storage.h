#ifndef STORAGE_H
#define STORAGE_H

#include "stdafx.h"
#include "Route.h"
#include "list"

class Storage
{
public:
    int saveToken(string &tokenString);
    int loadToken(string &tokenString);

    bool saveRoute(string &name, Route &route);
    bool loadRoute(string &name, Route &route);
    list<int> listSavedRouteId();
    bool listAvailableRoutes(list<string> &lstName);

    static Storage& getInstance();
    virtual ~Storage();

private:
    Storage();
};

#endif // STORAGE_H
