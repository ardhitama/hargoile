#ifndef ERRORREPORTING_H
#define ERRORREPORTING_H

#include "stdafx.h"

class Log
{
public:
    static Log& getInstance();
    void log(string strLog);
private:
    Log();
};

#endif // ERRORREPORTING_H
