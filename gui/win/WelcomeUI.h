#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include "../UIAbstract.h"

class WelcomeUI : virtual public UIAbstract
{
public:
    void toLinkedState();
    void toNotLinkedState();

};

#endif // WELCOMEUI_H
