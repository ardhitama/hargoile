#ifdef QT_MOBILITY

#include "QtmPositionRecorderImpl.h"

QtmPositionRecorderImpl::QtmPositionRecorderImpl() throw(Exception)
{
    qgeosource = QGeoPositionInfoSource::createDefaultSource(this);
    if(qgeosource == 0)
        throw Exception() << "Can't find GPS device" << TRACE();
    qgeosource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);

    updateInterval = 500; // initial update interval

    connect(qgeosource, SIGNAL(positionUpdated), this, SLOT(onUpdate()));
}

inline void QtmPositionRecorderImpl::start()
{
    qgeosource->startUpdates();
    setUpdateInterval(updateInterval);
}

void QtmPositionRecorderImpl::stop()
{
    qgeosource->stopUpdates();
}

void QtmPositionRecorderImpl::pause()
{
    // maintain GPS's lock but lower the update interval
    qgeosource->setUpdateInterval(3000);
}

inline void QtmPositionRecorderImpl::setUpdateInterval(int interval)
{
    qgeosource->setUpdateInterval(interval);
    updateInterval = interval;
}

void QtmPositionRecorderImpl::forceUpdate()
{
    qgeosource->requestUpdate();
}

void QtmPositionRecorderImpl::onUpdate(QGeoPositionInfo &qgeoinfo) throw(Exception)
{
    std::cout << qgeoinfo.coordinate().latitude() << qgeoinfo.coordinate().longitude() << qgeoinfo.coordinate().altitude() << endl;
}

#endif //QT_MOBILITY

