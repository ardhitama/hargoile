#ifndef LOCATIONRECORDER_H
#define LOCATIONRECORDER_H

#include "../LocationRecorderAbstract.h"

class LocationRecorder : public LocationRecorderAbstract
{
public:
	LocationRecorder();
	void start();
	void stop();
	void pause();
	void setUpdateInterval(int interval);
	void forceUpdate();
	void onUpdate();
};

#endif // LOCATIONRECORDER_H
