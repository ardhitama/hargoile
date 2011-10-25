#ifndef LOCATIONRECORDER_H
#define LOCATIONRECORDER_H

#include "../LocationRecorderAbstract.h"

class LocationRecorder
{
public:
        LocationRecorder(){}
    void start() throw(Exception);
    void stop() throw(Exception);
    void pause() throw(Exception);
    void setUpdateInterval(int interval) throw(Exception);
    void forceUpdate() throw(Exception);
    void onUpdate() throw(Exception);

private:
    int updateInterval;
};

#endif // LOCATIONRECORDER_H
