#ifndef NUMBER_H
#define NUMBER_H

#include <cmath>
#include <algorithm>
#include <cstdlib>
#include "../Exception/DebugInfo.h"

namespace hgl 
{
	// const double M_PI = 3.14159265358979323846f;

	inline float round(float num, int precision)
	{
		return std::floor(num * std::pow(10.0f,precision) + 0.5f)/std::pow(10.0f,precision);
	}

	inline double degToRad(double degree)
	{
		// returns degree * M_PI / 180.0f;
		return degree * 0.01745329251994329576922222222222f;
	}

	inline double radToDeg(double rad)
	{
		// return rad * 180.0f / M_PI;
		return rad * 57.295779513082320876846364344191f;
	}

	inline int rangedRand(unsigned int min, unsigned int max)
	{
		return (std::rand() % (max-min)+1) + min;
	}

	// http://mathworld.wolfram.com/CrossProduct.html
	// http://www.ltcconline.net/greenl/courses/107/vectors/dotcros.htm
	//  u = ai + bj + ck  and v = di + ej + fk
	//  u x v =  (bf - ce) i + (cd - af) j + (ae - bd) k

	inline double normalOfVectorCrossProduct(double x0, double y0, double z0, double x1, double y1, double z1)
	{
		return std::sqrt(std::pow((y0*z1 - z0*y1),2) + std::pow((z0*x1 - x0*z1),2) + std::pow((x0*y1 - y0*x1),2));
	}

	// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
	// d = |(x0-x1) x (x0-x2)| / |x2-x1|
	inline double pointToLineDistance(double lnX0, double lnY0, double lnZ0, double lnX1, double lnY1, double lnZ1, double ptX, double ptY, double ptZ)
	{
		return normalOfVectorCrossProduct(ptX-lnX0, ptY-lnY0, ptZ-lnZ0, ptX-lnX1, ptY-lnY1, ptZ-lnZ1) / std::sqrt(std::pow((lnX1-lnX0),2) + std::pow((lnY1-lnY0),2) + std::pow((lnZ1-lnZ0),2));
	}

	// vectorDistance
	// convert the inputs to euclidean coordinates while considering earth's oblate nature
	// inputs: geodetic coordinates in degrees
	// returns: distance between two geodetic points in meters
	// note: only accurate if distance is < 20 km
	// Will to convert latitude/longitude/altitude (LLA)
	// data into earth-centered/earth-fixed (ECEF) data.
	// will be optimal if used in near equator (altitude < 30 degrees)
	// basic theorem: http://mathworld.wolfram.com/SphericalCoordinates.html
	double vectorDistance(double lat1, double lon1, double alt1, double lat2, double lon2, double alt2);

	// greatCircleDistanceHaversine
	// calculate geodetic distance using haversine method
	// inputs: geodetic coordinates in degrees
	// returns: distance between two geodetic points in meters
	// note: precision lose if the distance is relatively short
	// http://mathworld.wolfram.com/GreatCircle.html
	double greatCircleDistanceHaversine(double lat1, double lon1, double lat2, double lon2);

	// calculate distance between two points in earth
	// input is in degrees
	// will not 100% accurate
	// unit is in meters
	double geodeticDistance(double lat1, double lon1, double alt1, double lat2, double lon2, double alt2);
}

#endif // NUMBER_H
