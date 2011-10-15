#include <iostream>
#include <ctime>

#include "Utility\String.h"
#include "Database\DatabaseAll.h"
#include "Utility\GeoPoint.h"


using namespace std;

void print(DatabaseResult rs)
{
	if(rs.getRowData().size() > 0)
	{
		for_each(rs.getRowData().begin(), rs.getRowData().end(), [](DatabaseRow row) {
			for_each(row.getColumn().begin(), row.getColumn().end(), [](DatabaseColumn col) {
				if(col.getColType() == col.TYPE_BIGINTEGER)
					cout << col.getInt64Data() << "\n";
				else if(col.getColType() == col.TYPE_INTEGER)
					cout << col.getIntData() << "\n";
				else if(col.getColType() == col.TYPE_BLOB)
					cout << &col.getBinData()[0] << "\n";
				else if(col.getColType() == col.TYPE_FLOAT)
					cout << col.getDoubleData() << "\n";
				else if(col.getColType() == col.TYPE_NULL)
					cout << "Null" << "\n";
				else if(col.getColType() == col.TYPE_TEXT)
					cout << col.getStrData() << "\n";
			});
		});
	}
	else
		cout << "No result\n";
}

struct RouteData
{
	string name;
	vector<GeoPoint> coord;
};


void generate(RouteData &genRoute, string routeName, int nMaxIteration)
{
	genRoute.name = routeName;

	time_t timeNow;
	struct tm *localTimeNow;
	time(&timeNow);
	localTimeNow = localtime(&timeNow);
	string strDate;
	//strftime(const_cast<char*>(strDate.data()), strDate.size(), "%Y-%m-%d %H:%M:%S", localTimeNow);

	auto *geoPoint = new GeoPoint();
	geoPoint->setLatitude(-7.782875);
	geoPoint->setLongitude(110.367098);
	geoPoint->setAltitude(60);
	geoPoint->setSpeed(30);
	geoPoint->setTime(timeNow);
	geoPoint->id = 1;

	genRoute.coord.push_back(*geoPoint);
	//delete GeoPoint;
	double radAngle = 0;

	//start moving
	for (int i = 1; i < nMaxIteration-1; ++i)
	{
		geoPoint->setLatitude(geoPoint->getLatitude() + Number::mt_rand(-10, 10) / 500000.0f);
		geoPoint->setLongitude(geoPoint->getLongitude() + Number::mt_rand(-10, 10) / 500000.0f);
		geoPoint->setAltitude(geoPoint->getAltitude() + Number::mt_rand(-3, 3));
		geoPoint->setSpeed(geoPoint->getSpeed() + Number::mt_rand(-10, 10));
		geoPoint->id = i+1;

		time(&timeNow);
		geoPoint->setTime(timeNow);

		genRoute.coord.push_back(*geoPoint);
	}

	time(&timeNow);
	radAngle = Number::degToRad(Number::mt_rand(-90, 360));
	geoPoint->setLatitude(geoPoint->getLatitude() + Number::mt_rand(-10, 10) / 500000.0f);
	geoPoint->setLongitude(geoPoint->getLongitude() + Number::mt_rand(-10, 10) / 500000.0f);
	geoPoint->setAltitude(geoPoint->getAltitude() + Number::mt_rand(-3, 3));
	geoPoint->setSpeed(0);
	geoPoint->setTime(timeNow);
	geoPoint->id=nMaxIteration;

	genRoute.coord.push_back(*geoPoint);
	delete geoPoint;
}

void simulateMovement(RouteData &genRoute, string routeName, int updateInterval, int distance, double speed)
{
	time_t timeNow;
	time(&timeNow);
	srand(timeNow);
	//distance : meter
	//time : second
	// (0, 0, 0, 1, 0, 0) 111315
	// (0, 0, 0, 0, 1, 0) 111319
	// (0, 0, 0, 1, 1, 0) 157423

	genRoute.name = routeName;
	GeoPoint gp(-7.782875f, 110.367098, 60, 60, 0);
	gp.id = 0;

	genRoute.coord.push_back(gp);

	int gpCount = 0, tick = 0;
	double radAngle = 0;
	int arrivalTimeout = distance/speed;
	//double speed = distance/arrivalTimeout; // 2.78m/s -> 10km/h
	double noise = 0; // degrees
	while(tick < arrivalTimeout)
	{
		if(tick % updateInterval == 0)
		{
			//radAngle = Number::degToRad(Number::mt_rand(0, 90));
			noise = (Number::mt_rand(0,50)/10) /157423.0f; // noise is -5 to 5 meters
			gp.setLatitude(gp.getLatitude() + ((speed/157423.0f) * updateInterval) + noise );
			gp.setLongitude(gp.getLongitude() + ((speed/157423.0f) * updateInterval) - noise );
			gp.setAltitude(gp.getAltitude());// + Number::mt_rand(-, 3));
			gp.setSpeed(speed);
			gp.id = ++gpCount;
			genRoute.coord.push_back(gp);
		}
		
		++tick;
	}

}

// might not give accurate result if tolerance > 5km
void dp(vector<GeoPoint> &vIn, vector<GeoPoint> &vOut, int i, int j, double tolerance)
{
	double tmp_dist = -1, dist = -1;
	int f = -1;
	static bool outFlag = true;
	if(i+1 < j)
	{
		for(int k=i+1; k<j; ++k) // find the max point distance from i-j line
		{
			tmp_dist = Number::pointToLineDistance(vIn[i].latitudeToX(), vIn[i].longitudeToY(), vIn[i].altitudeToZ(),
				vIn[j].latitudeToX(), vIn[j].longitudeToY(), vIn[j].altitudeToZ(),
				vIn[k].latitudeToX(), vIn[k].longitudeToY(), vIn[k].altitudeToZ());
			if(tmp_dist > dist) 
			{
				dist = tmp_dist;
				f = k;
			}
		}
		if(dist > tolerance)
			cout << "keep: id=" << vIn[f].id << " dist=" << dist << endl;
	}

	//dp orig: if(dist > tolerance) // tolerance is in meters
	if(dist > tolerance)
	{
		dp(vIn, vOut, i, f, tolerance);
		dp(vIn, vOut, f, j, tolerance);
	}
	else // if (dist==-1) or this is the last two node left from the divide and conquer
	{
		/*if(outFlag == true)
		{
			outFlag = false;
			vOut.push_back(vIn[i]);
		}
		else*/
			vOut.push_back(vIn[i]);
	}
}
// tolerance is in meters
void simplify(RouteData &routeData, double tolerance)
{
	vector<GeoPoint> &data = routeData.coord;
	vector<GeoPoint> result;

	dp(data, result, 0, data.size()-1, tolerance);
	result.push_back(data.back()); // must, dp doens't evaluate to the last node

	if(result.size() == 0)
		return;

	GeoPoint g0 = result[0];
	for_each(result.begin(), result.end(),
		[&](GeoPoint g) -> void {
			cout << "id= " << g.id << " " << g.getLatitude() << ", " << g.getLongitude() << " d from last: " << geodeticDistance(g0, g) << " m \n";
			g0 = g;
	} );

	cout << "size = " << result.size() << endl;
	cout << "-------" << endl;
}

int main(int argc, char** argv)
{
	/*
	try
	{
	DatabaseImpl db("./storage.hgl");
	DatabaseResult rs;

	db.exec("CREATE1 TABLE IF NOT EXISTS hargoile (pk int)");
	db.exec("CREATE TABLE IF NOT EXISTS config (pk int)");

	//db.exec("INSERT INTO hargoile VALUES(32)");
	//db.exec("INSERT INTO config VALUES(12)");

	//db.exec("DELETE FROM hargoile");
	//db.exec("DELETE FROM config");

	rs = db.exec("SELECT * FROM hargoile");
	print(rs);

	rs = db.exec("SELECT * FROM config");
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

	*/

	time_t timeNow;
	time(&timeNow);
	srand(timeNow);

	RouteData genRoute;
	//generate(genRoute, "auto gen", 30);
	simulateMovement(genRoute, "auto gen", 3, 200, 2.78);

	GeoPoint g0 = genRoute.coord[0];

	cout<< "Route name: " << genRoute.name << endl;
	for_each(genRoute.coord.begin(), genRoute.coord.end(),
		[&](GeoPoint g) -> void {
			cout << "id= " << g.id << " " << g.getLatitude() << ", " << g.getLongitude() << " d from last: " << geodeticDistance(g0, g) << " m \n";
			g0 = g;
	} );
	cout << "size = " << genRoute.coord.size() << endl;
	cout << "-------" << endl;

	simplify(genRoute, 1);
	
	system("pause");
	return 0;
}