#ifndef STORAGE_H
#define STORAGE_H

#include "config.h"
#include <list>
#include "../Utility/Database/DatabaseAll.h"
#include "../Technique/Singleton.h"
#include "Route.h"

class Storage : public Singleton<Storage>
{
public:
    void setAccessToken(String strToken);
    void getAccessToken(String strToken);

    void insertRoute(Route route);
    void getRoute(int routeId, Route &route);
    void deleteRoute(Route route);

    std::list<int> listSavedRouteId();
    void listAvailableRoutes(std::list<String> &lstName);

    void writeData(int type);

private:
    boost::shared_ptr<Database> db;

    Storage()
    {
        db = boost::shared_ptr<Database>(new DatabaseImpl("hgl.stor"));
        db->changeSchema("hargoile");
    }

    virtual ~Storage();
};

#endif // STORAGE_H
