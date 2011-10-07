#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <list>
#include "Assert.h"
#include "DebugInfo.h"
#include "../Utility/String.h"
#include "../Pattern/Singleton.h"

class DebugInfo; // forward declare

class DebugLog : public Singleton<DebugLog>
{
public:
    void operator += (DebugInfo &dbgInfo);
    void add(DebugInfo &dbgInfo);
private:
    std::list<DebugInfo> dbgLog;
};

inline void DebugLog::operator += (DebugInfo &dbgInfo)
{
    DebugLog::dbgLog.push_front(dbgInfo);
}

inline void DebugLog::add(DebugInfo &dbgInfo)
{
    DebugLog::dbgLog.push_front(dbgInfo);
}

#endif // DEBUGLOG_H
