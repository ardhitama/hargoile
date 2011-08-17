#ifndef STORAGE_H
#define STORAGE_H

#include "stdafx.h"
#include "Route.h"
#include "list"

#include "libs/sqllite3/sqlite3.h"

class Storage
{
public:
    bool setToken(string &strToken);
    void getToken(string &strToken);

    bool saveRoute(string &name, Route &route);
    bool loadRoute(string &name, Route &route);
    list<int> listSavedRouteId();
    bool listAvailableRoutes(list<string> &lstName);

    static Storage& getInstance();
    virtual ~Storage();

    void writeData(int type);
private:
    sqlite3 *sqliDB;
    int sqliStatus;
    Storage();
};

#endif // STORAGE_H
