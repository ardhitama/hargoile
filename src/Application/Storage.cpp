#include "Storage.h"

Storage::Storage() : db(Database("hgl.stor"))
{
    try
    {
        db.exec("CREATE TABLE IF NOT EXISTS config ( "
                "access_token char(128) not null unique "
                ");");

        db.exec("CREATE TABLE IF NOT EXISTS routes ( "
                "uuid char(38) primary key, "
                "name varchar(256) not null"
                ");");

        db.exec("CREATE TABLE IF NOT EXISTS route_points ( "
                "route_uuid char(36), "
                "point_order int not null, "
                "latitude double default 0, "
                "longitude double default 0, "
                "altitude double default 0, "
                "speed double default 0, "
                "time datetime default 0, "
                "accuracy double default 0, "
                "FOREIGN KEY (route_uuid) REFERENCES routes(route_uuid)"
                ");");

    } catch (Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
    }
}

void Storage::setAccessToken(String& strToken)
{
    try
    {
        db.exec("INSERT INTO config (access_token) VALUES ('" << strToken << "');");
    } catch (Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
    }
}

String Storage::getAccessToken()
{
    try
    {
        DatabaseResult res = db.exec("SELECT access_token FROM config;");
        if(res.getRowCount() == 0)
            return "";
        DatabaseRow row = res.getRowData().at(0);
        DatabaseColumn col = row.getColumnData().at(0);
        return col.getStrData();
    } catch (Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
        return "";
    }
}

void Storage::addRoute(Route& route)
{
    try
    {
        db.exec("INSERT INTO routes VALUES('" << route.getUUID() << "', '" << route.getName() << "');");

        int point_order = 0;

        db.exec("BEGIN;");
        /*
        std::for_each(std::begin(route.getData()), std::end(route.getData()), [&](GeoPoint gp) {
            db.exec("INSERT INTO route_points VALUES ('" << route.getUUID() << "', " << point_order << ", " << gp.getLatitude() << ", " << gp.getLongitude() << ", " << gp.getAltitude() << ", " << gp.getSpeed() << ", " << gp.getTime() << ", " << gp.getAccuracy() << "); ");
            ++point_order;
        });
        */

        for(unsigned int i=0; i<route.getData().size(); ++i)
        {
            GeoPoint &gp = route.getData()[i];
            db.exec("INSERT INTO route_points VALUES ('" << route.getUUID() << "', " << point_order << ", " << gp.getLatitude() << ", " << gp.getLongitude() << ", " << gp.getAltitude() << ", " << gp.getSpeed() << ", " << gp.getTime() << ", " << gp.getAccuracy() << "); ");
            ++point_order;
        }

        db.exec("COMMIT;");

    } catch (Exception &e)
    {
        db.exec("ROLLBACK;");
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
    }
}

Route Storage::getRoute(String& routeUUID)
{
    Route route;
    try
    {

        DatabaseResult res;
        res = db.exec("SELECT name FROM routes WHERE uuid = '" << routeUUID << "';");
        route.setName(res.getRowData().at(0).getColumnData().at(0).getStrData());

        res = db.exec("SELECT latitude, longitude, altitude, speed, time, accuracy FROM route_points WHERE route_uuid = '" << routeUUID << "' ORDER BY point_order ASC;");

        /*
        std::for_each(res.getRowData().begin(), res.getRowData().end(), [&](DatabaseRow row) {
            std::vector<DatabaseColumn> colData = row.getColumnData();
            double lat = colData[0].getDoubleData();
            double lon = colData[1].getDoubleData();
            double alt = colData[2].getDoubleData();

            double spd = colData[3].getDoubleData();
            long long tm = colData[4].getInt64Data();
            double acc = colData[5].getDoubleData();

            GeoPoint gp(lat, lon, alt, spd, tm, acc);

            route.addPoint(gp);
        });
    */
        for(unsigned int i=0; i<res.getRowData().size(); ++i)
        {
            std::vector<DatabaseColumn> &colData = res.getRowData()[i].getColumnData();
            double lat = colData[0].getDoubleData();
            double lon = colData[1].getDoubleData();
            double alt = colData[2].getDoubleData();

            double spd = colData[3].getDoubleData();
            long long tm = colData[4].getInt64Data();
            double acc = colData[5].getDoubleData();

            GeoPoint gp(lat, lon, alt, spd, tm, acc);

            route.addPoint(gp);
        }

    } catch (Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
    }
    return route;
}

void Storage::deleteRoute(String& routeUUID)
{
    try
    {
        db.exec("DELETE FROM routes WHERE uuid = '" << routeUUID << "';");
        db.exec("DELETE FROM route_points WHERE route_uuid = '" << routeUUID << "';");
    } catch (Exception &e)
    {
        LogOut::error(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
    }
}

std::map<String, String> Storage::listAllRoutes()
{
    std::map<String, String> rtMap;
    DatabaseResult res;
    res = db.exec("SELECT uuid, name FROM routes ORDER BY name ASC;");

    /*
    std::for_each(res.getRowData().begin(), res.getRowData().end(), [&](DatabaseRow row) {
        std::vector<DatabaseColumn> colData = row.getColumnData();
        rtMap.insert(std::pair<String, String>(colData[0].getStrData(), colData[1].getStrData()));
    });
    */

    for(unsigned int i=0; i<res.getRowData().size(); ++i)
    {
        std::vector<DatabaseColumn> &colData = res.getRowData()[i].getColumnData();
        rtMap.insert(std::pair<String, String>(colData[0].getStrData(), colData[1].getStrData()));
    }
    return rtMap;
}
