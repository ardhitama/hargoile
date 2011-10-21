#ifndef ROUTE_H
#define ROUTE_H

#include "../Algorithm/LineSimplification/DouglasPeucker.h"
#include "../Utility/String.h"
#include "../Utility/GeoPoint.h"
#include <algorithm>
#include <vector>
#include "../../libs/boost/uuid/uuid.hpp"
#include "../../libs/boost/uuid/uuid_generators.hpp"
#include "../../libs/boost/uuid/uuid_io.hpp"

class Route
{
public:
	Route()
	{
		boost::uuids::random_generator randGen;
		boost::uuids::uuid uuid =  randGen();

		Route::uuid = boost::uuids::to_string(uuid);
	}

	Route(String routeName)
	{
		boost::uuids::random_generator randGen;
		boost::uuids::uuid uuid =  randGen();

		Route::name = name;
		Route::uuid = boost::uuids::to_string(uuid);
	}

	inline void simplify(double tolerance)
	{
		route = dpSimplify<GeoPoint>(route, tolerance);
	}

	String toString()
	{
		String strRet;
		std::for_each(route.begin(), route.end(),
			[&](GeoPoint g) -> void {
				strRet << g.getLatitude() << ", " << g.getLongitude() << ", " << g.getAltitude() << "\n";
		} );
		return strRet;
	}

	inline std::vector<GeoPoint>& getData()
	{
		return route;
	}

	inline void setUUID(String strUuid)
	{
		uuid = strUuid;
	}

	inline void addPoint(const GeoPoint& newPoint)
	{
		route.push_back(newPoint);
	}

	inline String& getUUID()
	{
		return uuid;
	}

	inline void setName(String name)
	{
		Route::name = name;
	}	

	inline String& getName()
	{
		return name;
	}

private:
	std::vector<GeoPoint> route;
	String name, uuid;
};

#endif // ROUTE_H