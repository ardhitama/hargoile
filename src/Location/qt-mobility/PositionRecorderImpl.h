#ifdef QT_MOBILITY

#ifndef POSITIONRECORDERIMPL_H
#define POSITIONRECORDERIMPL_H

#include "PositionRecorder.h"

class PositionRecorderImpl : virtual PositionRecorder, QObject
{
    Q_OBJECT
public:
    PositionRecorderImpl() throw Exception;
    void start() throw Exception;
    void stop() throw Exception;
    void pause() throw Exception;
    void setUpdateInterval(int interval) throw Exception;
    void forceUpdate() throw Exception;
public slots:
    void onUpdate() throw Exception;
private:
    boost::shared_ptr<QGeoPositionInfoSource> qgeosource;
};

#endif // POSITIONRECORDERIMPL_H
#endif // QT_MOBILITY
