#ifndef LOCATIONRECORDERIMPL_H
#define LOCATIONRECORDERIMPL_H

#include "../LocationRecorder.h"

class LocationRecorderImpl
{
public:
	LocationRecorderImpl(){}
    void start() throw(Exception);
    void stop() throw(Exception);
    void pause() throw(Exception);
    void setUpdateInterval(int interval) throw(Exception);
    void forceUpdate() throw(Exception);
    void onUpdate() throw(Exception);

private:
    int updateInterval;
};

#endif // LOCATIONRECORDERIMPL_H