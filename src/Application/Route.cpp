#include "Route.h"

Route::Route()
{
    boost::uuids::random_generator randGen;
    boost::uuids::uuid uuid =  randGen();

    Route::uuid = boost::uuids::to_string(uuid);
}

Route::Route(String routeName)
{
    boost::uuids::random_generator randGen;
    boost::uuids::uuid uuid =  randGen();

    Route::name = routeName;
    Route::uuid = boost::uuids::to_string(uuid);
}

void Route::simplify(double tolerance)
{
    route = dpSimplify<GeoPoint>(route, tolerance);
}

String Route::toString()
{
    String strRet;
    /*
 std::for_each(std::begin(route), std::end(route), [&](GeoPoint &g) {
 strRet << g.getLatitude() << ", " << g.getLongitude() << ", " << g.getAltitude() << "\n";
 } );
 */

    for(unsigned int i = 0; i<route.size(); ++i)
    {
        strRet << route[i].getLatitude() << ", " << route[i].getLongitude() << ", " << route[i].getAltitude() << "\n";
    }

    return strRet;
}
