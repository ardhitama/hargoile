#ifndef MENUUI_H
#define MENUUI_H

#include "../UIAbstract.h"

class MenuUI : public UIAbstract
{
public:
    void setMenuType(int menuType);

    enum { WELCOME_MENU, RECORDER_MENU };
};

#endif // MENUUI_H
