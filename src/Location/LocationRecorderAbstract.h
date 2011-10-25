#ifndef LOCATIONRECORDERABSTRACT_H
#define LOCATIONRECORDERABSTRACT_H

class LocationRecorderAbstract
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    // interval is in msec
    virtual void setUpdateInterval(int interval) = 0;
    virtual void forceUpdate() = 0;
    virtual void onUpdate() = 0;
};

#endif // LOCATIONRECORDERABSTRACT_H
