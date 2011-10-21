#ifdef QT_MOBILITY
#ifndef LOCATIONRECORDERIMPL_H
#define LOCATIONRECORDERIMPL_H

#include "../LocationRecorder.H"

class LocationRecorderImpl : QObject
{
    Q_OBJECT
public:
	LocationRecorderImpl();
    void start() throw(Exception);
    void stop() throw(Exception);
    void pause() throw(Exception);
    void setUpdateInterval(int interval) throw(Exception);
    void forceUpdate() throw(Exception);
public slots:
    void onUpdate(QGeoPositionInfo &qgeoinfo) throw(Exception);
private:
    boost::shared_ptr<QGeoPositionInfoSource> qgeosource;
    int updateInterval;
};

#endif // LOCATIONRECORDERIMPL_H
#endif // QT_MOBILITY
