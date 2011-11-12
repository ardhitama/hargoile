#ifndef LOGOUT_H
#define LOGOUT_H

#include "../LogOutAbstract.h"
#include "../../../gui/UIAll.h"

class LogOut : LogOutAbstract
{
public:
    static void log(const String &msg)
    {
        PopupUI popUp(msg);
    }

    static void warning(const String &msg)
    {
        //
    }

    static void error(const String &msg)
    {
        PopupUI popUp(msg);
    }
};

#endif // LOGOUT_H
