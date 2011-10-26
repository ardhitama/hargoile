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
    Route();
    Route(String routeName);

    void simplify(double tolerance);

    String toString();

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
