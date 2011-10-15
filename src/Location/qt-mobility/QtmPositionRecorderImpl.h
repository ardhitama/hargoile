#ifdef QT_MOBILITY
#ifndef QTMPOSITIONRECORDERIMPL_H
#define QTMPOSITIONRECORDERIMPL_H

#include "../PositionRecorder.h"

class QtmPositionRecorderImpl : QObject
{
    Q_OBJECT
public:
    QtmPositionRecorderImpl();
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

#endif // QTMPOSITIONRECORDERIMPL_H
#endif // QT_MOBILITY
