#ifdef DEBUG
#include <vld.h>
#endif
#include <iostream>
#include <ctime>

#include <map>

#include "Utility\String.h"
#include "Database\DatabaseAll.h"
#include "Utility\GeoPoint.h"
#include "Algorithm\LineSimplification\DouglasPeucker.h"

#include "Application\Route.h"
#include "Application\MovementSimulator.h"
#include "Application\Storage.h"

using namespace std;

void print(DatabaseResult rs)
{
	if(rs.getRowData().size() > 0)
	{
		for_each(rs.getRowData().begin(), rs.getRowData().end(), [](DatabaseRow row) {
			for_each(row.getColumnData().begin(), row.getColumnData().end(), [](DatabaseColumn col) {
				if(col.getColType() == col.TYPE_BIGINTEGER)
					cout << col.getInt64Data();
				else if(col.getColType() == col.TYPE_INTEGER)
					cout << col.getIntData();
				else if(col.getColType() == col.TYPE_BLOB)
					cout << &col.getBinData()[0];
				else if(col.getColType() == col.TYPE_FLOAT)
					cout << col.getDoubleData();
				else if(col.getColType() == col.TYPE_NULL)
					cout << "Null";
				else if(col.getColType() == col.TYPE_TEXT)
					cout << col.getStrData();
				cout << " | ";
			});
			cout << endl;
		});
	}
	else
		cout << "No result\n";
}

int main(int argc, char** argv)
{
	try
	{
		DatabaseImpl db("./storage.hgl");
		DatabaseResult rs;

		db.exec("DROP TABLE IF EXISTS hargoile; DROP TABLE IF EXISTS hargoile2");

		db.exec("CREATE TABLE IF NOT EXISTS hargoile (pk int, data varchar(20))");

		db.exec("INSERT INTO hargoile VALUES(32, 'test1')");
		db.exec("INSERT INTO hargoile VALUES(43, 'test1')");

		db.exec("CREATE TABLE IF NOT EXISTS hargoile2 (pk int, data varchar(20))");

		db.exec("INSERT INTO hargoile2 VALUES(32, 'test2')");
		db.exec("INSERT INTO hargoile2 VALUES(43, 'test2')");
		db.exec("INSERT INTO hargoile2 VALUES(44, 'test2')");

		//db.exec("UPDATE hargoile SET data = hargoile2.data WHERE pk = hargoile2.pk");
		db.exec("UPDATE hargoile SET data = (SELECT data FROM hargoile2 WHERE hargoile.pk = hargoile2.pk)");
		//db.exec("INSERT INTO config VALUES(12)");

		//db.exec("DELETE FROM hargoile");
		//db.exec("DELETE FROM config");

		rs = db.exec("SELECT * FROM hargoile");
		print(rs);

		rs = db.exec(
			"SELECT name FROM sqlite_master "
			"WHERE type IN ('table','view') AND name NOT LIKE 'sqlite_%' "
			"UNION ALL "
			"SELECT name FROM sqlite_temp_master "
			"WHERE type IN ('table','view') "
			"ORDER BY 1");

		print(rs);
	} catch(Exception &e)
	{
		cout << e.getInfo() << " debug: " << e.getDebugInfo().getStrInfo() << endl;
	}


	time_t timeNow;
	time(&timeNow);
	srand(timeNow);

	Route genRoute;
	genRoute = simulateMovement("auto gen", 1, 1, 2.78);
	cout<< "uuid: " << genRoute.getUUID() << endl;

	GeoPoint g0 = genRoute.getData()[0];

	cout<< "Route name: " << genRoute.getName() << endl;
	for_each(genRoute.getData().begin(), genRoute.getData().end(),
	[&](GeoPoint g) -> void {
	cout << "id= " << g.id << " " << g.getLatitude() << ", " << g.getLongitude() << " d from last: " << geodeticDistance(g0, g) << " m \n";
	g0 = g;
	} );
	cout << "size = " << genRoute.getData().size() << endl;
	cout << "-------" << endl;

	vector<GeoPoint> lineOut = dpSimplify<GeoPoint>(genRoute.getData(), 1);

	for_each(lineOut.begin(), lineOut.end(),
	[&](GeoPoint g) -> void {
	cout << "id= " << g.id << " " << g.getLatitude() << ", " << g.getLongitude() << " d from last: " << geodeticDistance(g0, g) << " m \n";
	g0 = g;
	} );

	Storage::getInstance().addRoute(genRoute);
	map<String, String> rtMap = Storage::getInstance().listAllRoutes();

	for_each(rtMap.begin(), rtMap.end(), [](pair<String, String> rtPair) {
			cout << rtPair.first << " - " << rtPair.second << endl;
		});

	//Storage::getInstance().getRoute();


	cout << "size = " << lineOut.size() << endl;
	cout << "-------" << endl;
	system("pause");
	return 0;
}