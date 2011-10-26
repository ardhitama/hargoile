#ifndef LOCATIONRECORDER_H
#define LOCATIONRECORDER_H

#include "../LocationRecorderAbstract.h"

class LocationRecorder
{
public:
    LocationRecorder(){}
    void start();
    void stop();
    void pause();
    void setUpdateInterval(int interval);
    void forceUpdate();
    void onUpdate();

private:
    int updateInterval;
};

#endif // LOCATIONRECORDER_H
