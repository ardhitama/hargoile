#ifndef LOCATIONALL_H
#define LOCATIONALL_H

#include "LocationRecorderAbstract.h"

#ifdef TARGET_QTM
#include "qtm/LocationRecorder.h"
#endif // QT_MOBILITY

#ifdef TARGET_WIN32
#include "win/LocationRecorder.h"
#endif // WIN32

#endif // LOCATIONALL_H
