#include "LocationRecorder.h"
#include "../../Application/Hargoile.h"

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

void LocationRecorder::stop() throw(Exception){}
void LocationRecorder::pause() throw(Exception){}
void LocationRecorder::setUpdateInterval(int interval) throw(Exception){}
void LocationRecorder::forceUpdate() throw(Exception){}

void LocationRecorder::onUpdate(QGeoPositionInfo qgeoinfo)
{
    Hargoile::getInstance().addNewPosition(qgeoinfo.coordinate().toString().toStdString());
}
