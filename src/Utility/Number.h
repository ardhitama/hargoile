#ifndef NUMBER_H
#define NUMBER_H

#include <cmath>
#include <cstdlib>
#include "../Exception/DebugInfo.h"

namespace Number 
{
	double M_PI = 3.14159265358979323846f;

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

	int mt_rand(unsigned int min, unsigned int max)
	{
		return (std::rand() % (max-min)+1) + min;
	}

	// http://mathworld.wolfram.com/CrossProduct.html
	// http://www.ltcconline.net/greenl/courses/107/vectors/dotcros.htm
	//  u = ai + bj + ck  and v = di + ej + fk 
	//  u x v =  (bf - ce) i + (cd - af) j + (ae - bd) k 
	inline double crossProduct(double x0, double y0, double z0, double x1, double y1, double z1)
	{
		return (y0*z1 - z0*y1) + (z0*x1 - x0*z1) + (x0*y1 - y1*x0);
	}

	// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
	inline double pointToLineDistance(double lnX0, double lnY0, double lnZ0, double lnX1, double lnY1, double lnZ1, double ptX, double ptY, double ptZ)
	{
		return std::abs(crossProduct(ptX-lnX0, ptY-lnY0, ptZ-lnZ0, ptX-lnX1, ptY-lnY1, ptZ-lnZ1)) / std::abs((lnX1-lnX0) + (lnY1-lnY0) + (lnZ1-lnZ0));
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
	double vectorDistance(double lat1, double lon1, double alt1, double lat2, double lon2, double alt2)
	{
		lat1 = degToRad(lat1);
		lon1 = degToRad(lon1);
		lat2 = degToRad(lat2);
		lon2 = degToRad(lon2);

		// ellipsoid defining parameters according WGS84
		double a = 6378137.0f; // earth equatorial radius in meters (± 2m) -> semimajor axis
		double f = 1.0f / 298.257223563f; // flattening parameter, f = (a-b)/a
		// derived WGS84 geometric constants
		double b = 6356752.3142; // semiminor axis (pole to pole),  b = a * (1-f) ˜ 6356752.3142 m
		double e2 = 6.69437999014e-3; // First Eccentricity Squared. e2 = 1-b^2/a^2 = 2f-f^2

		// http://en.wikipedia.org/wiki/Geodetic_system -> From geodetic to ECEF
		double N1 = a / std::sqrt(1 - e2 * std::pow(std::sin(lat1), 2)); // radius of curvature in prime vertical
		double N2 = a / std::sqrt(1 - e2 * std::pow(std::sin(lat2), 2));

		// convert lat1, lon1, alt1 to spherical coordinates
		double x1 = (N1 + alt1) * std::cos(lat1) * std::cos(lon1);
		double y1 = (N1 + alt1) * std::cos(lat1) * std::sin(lon1);
		double z1 = (N1 * (1-e2) + alt1) * std::sin(lat1);

		// convert lat2, lon2, alt2 to spherical coordinates
		double x2 = (N2 + alt2) * std::cos(lat2) * std::cos(lon2);
		double y2 = (N2 + alt2) * std::cos(lat2) * std::sin(lon2);
		double z2 = (N2 * (1-e2) + alt2) * std::sin(lat2);

		// straight distance between 2 points in 3d coordinate
		return std::sqrt( std::pow(x2-x1, 2) + std::pow(y2-y1, 2) + std::pow(z2-z1, 2) );
	}

	// greatCircleDistanceHaversine
	// calculate geodetic distance using haversine method
	// inputs: geodetic coordinates in degrees
	// returns: distance between two geodetic points in meters
	// note: precision lose if the distance is relatively short
	// http://mathworld.wolfram.com/GreatCircle.html
	double greatCircleDistanceHaversine(double lat1, double lon1, double lat2, double lon2)
	{
		// ellipsoid defining parameters according WGS84
		// R = 6378137.0f = earth equatorial radius in meters (± 2m) -> semimajor axis

		//
		/* http://www.faqs.org/faqs/geography/infosystems-faq/
		Q5.1: What is the best way to calculate the great circle distance (which deliberately ignores elevation differences) between 2 points?
		(This answer was prepared by Robert G. Chamberlain of Caltech (JPL):
		rgc@solstice.jpl.nasa.gov and reviewed on the comp.infosystems.gis newsgroup in Oct 1996.)

		Haversine Formula (from R.W. Sinnott, "Virtues of the Haversine", Sky and Telescope, vol. 68, no. 2, 1984, p. 159):
		dlon = lon2 - lon1
		dlat = lat2 - lat1
		a = sin^2(dlat/2) + cos(lat1) * cos(lat2) * sin^2(dlon/2)
		c = 2 * arcsin(min(1,sqrt(a)))
		d = R * c

		The min() function protects against possible roundoff errors that
		could sabotage computation of the arcsine if the two points are
		very nearly antipodal (that is, on opposide sides of the Earth).
		Under these conditions, the Haversine Formula is ill-conditioned
		(see the discussion below), but the error, perhaps as large as
		2 km (1 mi), is in the context of a distance near 20,000 km
		(12,000 mi).


		! We are not using Law of Cosines for Spherical Trigonometry:
		a = sin(lat1) * sin(lat2)
		b = cos(lat1) * cos(lat2) * cos(lon2 - lon1)
		c = arccos(a + b)
		d = R * c

		Although the above formula is mathematically exact, it is unreliable
		for small distances because the inverse cosine is ill-conditioned.
		Sinnott (in the article cited above) offers the following table
		to illustrate the point:
		cos (5 degrees) = 0.996194698
		cos (1 degree)  = 0.999847695
		cos (1 minute)  = 0.9999999577
		cos (1 second)  = 0.9999999999882
		cos (0.05 sec)  = 0.999999999999971
		A computer carrying seven significant figures cannot distinguish
		the cosines of any distances smaller than about one minute of arc.
		*/

		lat1 = degToRad(lat1);
		lon1 = degToRad(lon1);
		lat2 = degToRad(lat2);
		lon2 = degToRad(lon2);

		double a = pow(sin((lat2-lat1))/2.0f, 2) + cos(lat1) * cos(lat2) * pow(sin((lon2-lon1)/2.0f), 2);
		return 6378137.0f * 2 * std::asin(std::min<double>(1.0f, std::sqrt(a)));
	}

	// calculate distance between two points in earth
	// input is in degrees
	// will not 100% accurate
	// unit is in meters
	double geodeticDistance(double lat1, double lon1, double alt1, double lat2, double lon2, double alt2)
	{
		bool isInputError = false;

		// Check inputs
		// http://docs.obspy.org/coverage/_opt_obspy_python_src_obspy_obspy_signal_obspy_signal_rotate.html
		if (lat1 > 90 || lat1 < -90)
		{
			DebugInfo("Latitude of point 1 out of bounds (-90 <= lat1 <=90)", DebugInfo::Warning);
			isInputError = true;
		}
		while (lon1 > 180)
			lon1 -= 360;
		while (lon1 < -180) 
			lon1 += 360;
		if (lat2 > 90 || lat2 < -90)
		{
			DebugInfo("Latitude of point 2 out of bounds (-90 <= lat2 <=90)", DebugInfo::Warning);
			isInputError = true;
		}
		while (lon2 > 180)
			lon2 -= 360;
		while (lon2 < -180)
			lon2 += 360;

		// ardhi's
		if(alt1 < -6340000) // approximate earth's core depth
		{
			DebugInfo("Altitude of point 1 out of bounds (alt1 >= -6340000)", DebugInfo::Warning);
			isInputError = true;
		}
		if(alt2 < -6340000) // approximate earth's core depth
		{
			DebugInfo("Altitude of point 2 out of bounds (alt1 >= -6340000)", DebugInfo::Warning);
			isInputError = true;
		}

		if(isInputError)
			return -1;

		if ((std::abs(lat1 - lat2) < 1e-8) && (std::abs(lon1 - lon2) < 1e-8) && (std::abs(alt1 - alt1) < 1e-8)) // 1e8 = 0.00000001  
			return 0.0f;

		/* http://www.faqs.org/faqs/geography/infosystems-faq/
		Pythagorean Theorem
		d = sqrt((X2 - X1)^2 + (Y2 - Y1)^2)
		will result in an error of
		less than 30 meters (100 ft) for latitudes less than 70 degrees
		less than 20 meters ( 66 ft) for latitudes less than 50 degrees
		less than  9 meters ( 30 ft) for latitudes less than 30 degrees
		*/
		if(lat1 > 30 || lat1 < -30 || lat2 > 30 || lat2 < -30) // vector based distance will results calculation error > 9 meters if latitude is < 30 degrees
			return greatCircleDistanceHaversine(lat1, lon1, lat2, lon2);

		if(vectorDistance(lat1, lon1, 0, lat2, lon2, 0) > 5000) // is distance > 5 km, use haversine method, but neglects altitude
			return greatCircleDistanceHaversine(lat1, lon1, lat2, lon2);

		return vectorDistance(lat1, lon1, alt1, lat2, lon2, alt2);
	}

};

#endif // NUMBER_H