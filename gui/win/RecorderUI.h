#ifndef RECORDERUI_H
#define RECORDERUI_H

#include "../UIAbstract.h"
#include "../../src/Utility/String.h"

class RecorderUI : protected UIAbstract
{
public:
	void appendPositionListView(const String &str) {}
	void toRecordingState(){}
	void toStoppedState(){}
	void toPausedState(){}

	void show();
	void hide();
	void close();
	void destroy();
	void setMinimized();
	void setMaximized();
};

#endif // RECORDERUI_H
