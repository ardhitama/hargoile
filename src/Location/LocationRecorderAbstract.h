#ifndef LOCATIONRECORDERABSTRACT_H
#define LOCATIONRECORDERABSTRACT_H

class LocationRecorderAbstract
{
public:
    virtual void start() {};
    virtual void stop() {};
    virtual void pause() {};
    // interval is in msec
    virtual void setUpdateInterval(int /*interval*/) {};
    virtual void forceUpdate() {};
    virtual void onUpdate() {};
};

#endif // LOCATIONRECORDERABSTRACT_H
