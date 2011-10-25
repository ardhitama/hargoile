#ifndef LOGOUT_H
#define LOGOUT_H

#include "../LogOutAbstract.h"
#include <iostream>

class LogOut : LogOutAbstract
{
public:
    static void log(const String &msg)
    {
        std::cout << "Log: " << msg << std::endl;
    }

    static void warning(const String &msg)
    {
        std::cout << "Warning: " << msg << std::endl;
    }

    static void error(const String &msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
};

#endif // LOGOUT_H
