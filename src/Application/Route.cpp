#include "Route.h"

Route::Route()
{
    generateUUID();
}

Route::Route(String routeName)
{
    generateUUID();
    Route::name = routeName;
}

void Route::generateUUID()
{
    boost::uuids::random_generator randGen;
    boost::uuids::uuid uuidOb =  randGen();

    Route::uuid = boost::uuids::to_string(uuidOb);
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
