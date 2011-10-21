#ifndef STORAGE_H
#define STORAGE_H

#include "config.h"
#include "../Database/DatabaseAll.h"
#include "../Technique/Singleton.h"
#include "Route.h"
#include "win/ErrorNotificationImpl.h"
#include <algorithm>
#include <map>

class Storage : public Singleton<Storage>
{
public:
	Storage() : db(DatabaseImpl("hgl.stor"))
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
			ErrorNotificationImpl::textOut(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
		}
	}

	void setAccessToken(String& strToken)
	{
		try
		{
			db.exec("INSERT INTO config (access_token) VALUES ('" << strToken << "');");
		} catch (Exception &e)
		{
			ErrorNotificationImpl::textOut(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
		}
	}

	String getAccessToken()
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
			ErrorNotificationImpl::textOut(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
			return "";
		}
	}

	void addRoute(Route& route)
	{
		try
		{
			db.exec("INSERT INTO routes VALUES('" << route.getUUID() << "', '" << route.getName() << "');");

			std::for_each(std::begin(route.getData()), std::end(route.getData()), [&](GeoPoint gp) {
				db.exec("INSERT INTO route_points VALUES('" << route.getUUID() << "', " << gp.getLatitude() << ", " << gp.getLongitude() << ", " << gp.getAltitude() << ", " << gp.getSpeed() << ", " << gp.getTime() << ", " << gp.getAccuracy() << ");");
			});

		} catch (Exception &e)
		{
			ErrorNotificationImpl::textOut(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
		}
	}

	Route getRoute(String& routeUUID)
	{
		try
		{
			Route route;
			DatabaseResult res;
			res = db.exec("SELECT name FROM routes WHERE uuid = '" << routeUUID << "';");
			route.setName(res.getRowData().at(0).getColumnData().at(0).getStrData());

			res = db.exec("SELECT latitude, longitude, altitude, speed, time, accuracy FROM route_points WHERE uuid = '" << routeUUID << "';");

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
		} catch (Exception &e)
		{
			ErrorNotificationImpl::textOut(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
		}
	}

	void deleteRoute(String& routeUUID)
	{
		try
		{
			db.exec("DELETE FROM routes WHERE uuid = '" << routeUUID << "';");
			db.exec("DELETE FROM route_points WHERE route_uuid = '" << routeUUID << "';");
		} catch (Exception &e)
		{
			ErrorNotificationImpl::textOut(e.getInfo() << " (" << e.getDebugInfo().getStrInfo() << ")");
		}
	}

	std::map<String, String> listAllRoutes()
	{
		std::map<String, String> rtMap;
		DatabaseResult res;
		res = db.exec("SELECT uuid, name FROM routes;");
		std::for_each(res.getRowData().begin(), res.getRowData().end(), [&](DatabaseRow row) {
			std::vector<DatabaseColumn> colData = row.getColumnData();
			rtMap.insert(std::pair<String, String>(colData[0].getStrData(), colData[1].getStrData()));
		});
		return rtMap;
	}

private:
	DatabaseImpl db;   
};

#endif // STORAGE_H
