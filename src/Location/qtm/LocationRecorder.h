#ifndef LOCATIONRECORDER_H
#define LOCATIONRECORDER_H

#include "../../../libs/boost/shared_ptr.hpp"

#include "../LocationRecorderAbstract.h"
#include "../../Exception/ExceptionAll.h"

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

class LocationRecorder : public QObject
{
    Q_OBJECT
public:
    LocationRecorder()
    {
        qGeoSource.reset(QtMobility::QGeoPositionInfoSource::createDefaultSource(0));
    }
    void start() throw(Exception);
    void stop() throw(Exception);
    void pause() throw(Exception);
    void setUpdateInterval(int interval) throw(Exception);
    void forceUpdate() throw(Exception);
public slots:
    void onUpdate(QtMobility::QGeoPositionInfo &qgeoinfo)
    {
        //
    }
private:
    boost::shared_ptr<QtMobility::QGeoPositionInfoSource> qGeoSource;
    int updateInterval;
};

#endif // LOCATIONRECORDER_H
