#ifndef GEOCALC_H
#define GEOCALC_H

class GeoCalc
{
public:
	// calculate distance between two points in earth
	// will not 100% accurate
	double geodeticDistance(double lat1, double lon1, double alt1, double lat2, double lon2, double alt2);

private:
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
};

#endif // GEOCALC_H
