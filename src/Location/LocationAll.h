#ifndef LOCATIONALL_H
#define LOCATIONALL_H

#include "LocationRecorder.h"

#ifdef QT_MOBILITY
#include "qtm/LocationRecorderImpl.h"
#endif

#ifdef WIN32
#include "win/LocationRecorderImpl.h"
#endif

#endif // LOCATIONALL_H
