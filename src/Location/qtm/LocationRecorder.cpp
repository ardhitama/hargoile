#include "LocationRecorder.h"
#include "../../Application/Hargoile.h"

#include <QDateTime>

LocationRecorder::LocationRecorder()
{
    qGeoSource.reset(QGeoPositionInfoSource::createDefaultSource(0));
    qGeoSource->setUpdateInterval(1000);
    connect(qGeoSource.get(), SIGNAL(positionUpdated(QGeoPositionInfo)), SLOT(onUpdate(QGeoPositionInfo)));
}

void LocationRecorder::start() throw(Exception)
{
    qGeoSource->startUpdates();
}

void LocationRecorder::stop() throw(Exception)
{
    qGeoSource->stopUpdates();
}

void LocationRecorder::pause() throw(Exception){}
void LocationRecorder::setUpdateInterval(int interval) throw(Exception){}
void LocationRecorder::forceUpdate() throw(Exception){}

void LocationRecorder::onUpdate(QGeoPositionInfo qgeoinfo)
{
    GeoPoint gp;
    gp.setLongitude(qgeoinfo.coordinate().longitude());
    gp.setLatitude(qgeoinfo.coordinate().latitude());
    gp.setAltitude(qgeoinfo.coordinate().altitude());
    gp.setHAccuracy(qgeoinfo.attribute(QGeoPositionInfo::HorizontalAccuracy));
    gp.setVAccuracy(qgeoinfo.attribute(QGeoPositionInfo::VerticalAccuracy));
    gp.setHSpeed(qgeoinfo.attribute(QGeoPositionInfo::GroundSpeed));
    gp.setVSpeed(qgeoinfo.attribute(QGeoPositionInfo::VerticalSpeed));
    gp.setTime(QDateTime::currentDateTime().toTime_t());
    Hargoile::getInstance().addNewPosition(gp);
}
