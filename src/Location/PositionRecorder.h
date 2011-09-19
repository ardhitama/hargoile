#ifndef POSITIONRECORDER_H
#define POSITIONRECORDER_H

#include "stdafx.h"

class PositionRecorder
{
public:
    virtual void start() throw Exception = 0;
    virtual void stop() throw Exception = 0;
    virtual void pause() throw Exception = 0;
    // interval is in msec
    virtual void setUpdateInterval(int interval) throw Exception;
    virtual void forceUpdate() throw Exception;
    virtual void onUpdate() throw Exception = 0;
};

#endif // POSITIONRECORDER_H
