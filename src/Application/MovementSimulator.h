#ifndef MOVEMENTSIMULATOR_H
#define MOVEMENTSIMULATOR_H

#include "../Utility/String.h"
#include "Route.h"

Route simulateMovement(String routeName, int updateInterval, int distance, double speed)
{
    Route genRoute;
    time_t timeNow;
    time(&timeNow);
    srand(timeNow);
    //distance : meter
    //time : second
    // (0, 0, 0, 1, 0, 0) 111315
    // (0, 0, 0, 0, 1, 0) 111319
    // (0, 0, 0, 1, 1, 0) 157423 -> 1 degree north, 1 degree east from (0,0) = 157423 meters.

    genRoute.setName(routeName);
    GeoPoint gp(-7.782875f, 110.367098, 60, 60, 0, 0);
    gp.id = 0;

    genRoute.addPoint(gp);

    int gpCount = 0, tick = 0;
    double radAngle = 0;
    int arrivalTimeout = distance/speed;
    //double speed = distance/arrivalTimeout; // 2.78m/s -> 10km/h
    double noise = 0; // degrees
    while(tick < arrivalTimeout)
    {
        if(tick % updateInterval == 0)
        {
            //radAngle = Number::degToRad(Number::rangedRand(0, 90));
            noise = (Number::rangedRand(0,50)/10) / 111315.0f; // noise is 0 to 5 meters
            gp.setLatitude(gp.getLatitude() + ((speed/ 111315.0f) * updateInterval) + noise );
            gp.setLongitude(gp.getLongitude() + ((speed/ 111315.0f) * updateInterval) - noise );
            gp.setAltitude(gp.getAltitude());// + Number::rangedRand(-, 3));
            gp.setSpeed(speed);
            gp.id = ++gpCount;
            genRoute.addPoint(gp);
        }
        ++tick;
    }

    if(genRoute.getData().size() == 1)
    {
        GeoPoint gp(-7.782875f, 110.367098, 60, 60, 0, 0);
        gp.id = genRoute.getData().size();
        genRoute.addPoint(gp);
    }
    return genRoute;
}

// Deprecated
/*
void generate(RouteData &genRoute, String routeName, int nMaxIteration)
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
        geoPoint->setLatitude(geoPoint->getLatitude() + Number::rangedRand(-10, 10) / 500000.0f);
        geoPoint->setLongitude(geoPoint->getLongitude() + Number::rangedRand(-10, 10) / 500000.0f);
        geoPoint->setAltitude(geoPoint->getAltitude() + Number::rangedRand(-3, 3));
        geoPoint->setSpeed(geoPoint->getSpeed() + Number::rangedRand(-10, 10));
        geoPoint->id = i+1;

        time(&timeNow);
        geoPoint->setTime(timeNow);

        genRoute.coord.push_back(*geoPoint);
    }

    time(&timeNow);
    radAngle = Number::degToRad(Number::rangedRand(-90, 360));
    geoPoint->setLatitude(geoPoint->getLatitude() + Number::rangedRand(-10, 10) / 500000.0f);
    geoPoint->setLongitude(geoPoint->getLongitude() + Number::rangedRand(-10, 10) / 500000.0f);
    geoPoint->setAltitude(geoPoint->getAltitude() + Number::rangedRand(-3, 3));
    geoPoint->setSpeed(0);
    geoPoint->setTime(timeNow);
    geoPoint->id=nMaxIteration;

    genRoute.coord.push_back(*geoPoint);
    delete geoPoint;
}
*/

#endif // MOVEMENTSIMULATOR_H
