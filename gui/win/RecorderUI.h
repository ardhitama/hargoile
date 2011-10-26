#ifndef RECORDERUI_H
#define RECORDERUI_H

#include "../UIAbstract.h"

class RecorderUI : protected UIAbstract
{
public:
	void show();
	void hide();
	void close();
	void destroy();
	void setMinimized();
	void setMaximized();
};

#endif // RECORDERUI_H
