#ifdef QT_MOBILITY

#include "PositionRecorderImpl.h"

PositionRecorderImpl::PositionRecorderImpl() throw Exception
{
    qgeosource = QGeoPositionInfoSource::createDefaultSource(this);
    if(qgeosource == 0)
        throw Exception() << ;
    qgeosource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
}

#endif //QT_MOBILITY

