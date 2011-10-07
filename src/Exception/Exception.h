#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <list>
#include <exception>
#include "Assert.h"
#include "DebugInfo.h"
#include "../Utility/String.h"

class Exception : virtual public std::exception
{
public:
    Exception();
    Exception(char *strInfo);
    Exception(String strInfo);
    Exception(DebugInfo dbgInfo);
    Exception(String strInfo, DebugInfo dbgInfo);

    virtual ~Exception() throw();

    void getInfo(String &strInfoOut);
    void getDebugInfo(DebugInfo &dbgInfoOut);

    friend Exception operator << (Exception ex, String strInfo);
    friend Exception operator << (Exception ex, char *strInfo);
    friend Exception operator << (Exception ex, DebugInfo dbgInfo);

private:
    String strInfo; // user friendly message
    DebugInfo dbgInfo; // info for debugging purpose
};

inline Exception operator << (Exception ex, String strInfo)
{
    ex.strInfo.append(strInfo);
    return ex;
}

inline Exception operator << (Exception ex, char *strInfo)
{
    ex.strInfo.append(String(strInfo));
    return ex;
}

inline Exception operator << (Exception ex, DebugInfo dbgInfo)
{
    ex.dbgInfo = dbgInfo;
    DebugLog::getInstance()->add(dbgInfo);
    return ex;
}

Exception::Exception()
{
    Exception::strInfo = String();
}

Exception::Exception(String strInfo)
{
    Exception::strInfo = strInfo;
}

Exception::Exception(char *strInfo)
{
    Exception::strInfo = String(strInfo);
}

Exception::Exception(DebugInfo dbgInfo)
{
    Exception::dbgInfo = dbgInfo;
    DebugLog::getInstance()->add(dbgInfo);
}

Exception::Exception(String strInfo, DebugInfo dbgInfo)
{
    Exception::strInfo = strInfo;
    Exception::dbgInfo = dbgInfo;
    DebugLog::getInstance()->add(dbgInfo);
}

#endif // EXCEPTION_H
