#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include "../UIAbstract.h"

class WelcomeUI : protected UIAbstract
{
public:
	void show();
	void hide();
	void close();
	void destroy();
	void setMinimized();
	void setMaximized();
};

#endif // WELCOMEUI_H