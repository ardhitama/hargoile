#ifndef GEOPOINT_H
#define GEOPOINT_H

#include "Point.h"
#include "Number.h"


class GeoPoint : public Point
{
public:
	int id;
	GeoPoint::GeoPoint()
	{
		GeoPoint::latitude = 0;
		GeoPoint::longitude = 0;
		GeoPoint::altitude = 0;
		GeoPoint::speed = 0;
		GeoPoint::time = 0;
	}

	GeoPoint::GeoPoint(double latitude, double longitude, double altitude, double speed, long long time = 0)
	{
		GeoPoint::latitude = latitude;
		GeoPoint::longitude = longitude;
		GeoPoint::altitude = altitude;
		GeoPoint::speed = speed;
		GeoPoint::time = time;
	}

	void setLatitude(double latitude)
	{
		if (latitude > 90 || latitude < -90)
		{
			DebugInfo("Latitude of point 1 out of bounds (-90 <= latitude <=90)", DebugInfo::Warning);
		}
		GeoPoint::latitude = latitude;
		GeoPoint::x = latitudeToX();
	}

	void setLongitude(double longitude)
	{
		while (longitude > 180)
			longitude -= 360;
		while (longitude < -180) 
			longitude += 360;
		GeoPoint::longitude = longitude;
		GeoPoint::y = longitudeToY();
	}

	void setAltitude(double altitude)
	{
		if(altitude < -6340000) // approximate earth's core depth
		{
			DebugInfo("Altitude of point 1 out of bounds (altitude >= -6340000)", DebugInfo::Warning);
			altitude = -6340000;
		}
		GeoPoint::altitude = altitude;
		GeoPoint::z = altitudeToZ();
	}

	void setSpeed(double speed)
	{
		if(speed < 0)
		{
			DebugInfo("Speed is negative (speed >= 0)", DebugInfo::Warning);
			speed = 0;
		}
		GeoPoint::speed = speed;
	}

	void setTime(long long time)
	{
		if(time < 0)
		{
			DebugInfo("Time is negative (time >= 0)", DebugInfo::Warning);
		}
		GeoPoint::time = time;
	}

	inline double getLatitude()
	{
		return latitude;
	}

	inline double getLongitude()
	{
		return longitude;
	}

	inline double getAltitude()
	{
		return altitude;
	}

	inline double getSpeed()
	{
		return speed;
	}

	inline long long getTime()
	{
		return time;
	}

	// convert from geodetic coordinates to spherical coordinates in meters
	inline double GeoPoint::latitudeToX()
	{
		double lat = Number::degToRad(GeoPoint::latitude);
		double lon = Number::degToRad(GeoPoint::longitude);
		double N =  6378137.0f / sqrt(1 -  6.69437999014e-3 * std::pow(std::sin(lat), 2));
		return (N + GeoPoint::altitude) * std::cos(lat) * std::cos(lon);
	}

	inline double GeoPoint::longitudeToY()
	{
		double lat = Number::degToRad(GeoPoint::latitude);
		double lon = Number::degToRad(GeoPoint::longitude);
		double N =  6378137.0f / std::sqrt(1 -  6.69437999014e-3 * std::pow(std::sin(lat), 2));
		return (N + GeoPoint::altitude) * std::cos(lat) * std::sin(lon);
	}
	inline double GeoPoint::altitudeToZ()
	{
		double lat = Number::degToRad(GeoPoint::latitude);
		double N =  6378137.0f / sqrt(1 -  6.69437999014e-3 * std::pow(std::sin(lat), 2));
		return (N * (1-6.69437999014e-3) + GeoPoint::altitude) * std::sin(lat);
	}

	// get distance between this GeoPoint and other GeoPoint
	inline double geodeticDistance(const GeoPoint &gp)
	{
		return Number::geodeticDistance(GeoPoint::latitude, GeoPoint::longitude, GeoPoint::altitude, gp.latitude, gp.longitude, gp.altitude);
	}

	friend double geodeticDistance(const GeoPoint &g1, const GeoPoint &g2);

protected:
	double latitude, longitude, altitude, speed;
	long long time;	// in seconds
};

inline double geodeticDistance(const GeoPoint &g1, const GeoPoint &g2)
{
	return Number::geodeticDistance(g1.latitude, g1.longitude, g1.altitude, g2.latitude, g2.longitude, g2.altitude);
}


#endif // GEOPOINT_H