#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include "../Utility/String.h"
#include "DebugLog.h"

class DebugInfo
{
public:
    enum {Log = 0, Notice, Warning, Error};
    DebugInfo();
    DebugInfo(char *strInfo, int infoPriority, int infoSignature);
    DebugInfo(String &strInfo, int infoPriority, int infoSignature);
private:
    String strInfo;
    int infoSignature;
    int infoPriority;
};

DebugInfo::DebugInfo()
{
    DebugInfo::infoPriority = DebugInfo::Log;
    DebugInfo::infoSignature = -1;
}

DebugInfo::DebugInfo(char *strInfo, int infoPriority = DebugInfo::Log, int infoSignature = -1)
{
    DebugInfo::strInfo = String(strInfo);
    DebugInfo::infoPriority = infoPriority;
    DebugInfo::infoSignature = infoSignature;
}

DebugInfo::DebugInfo(String &strInfo, int infoPriority = DebugInfo::Log, int infoSignature = -1)
{
    DebugInfo::strInfo = strInfo;
    DebugInfo::infoPriority = infoPriority;
    DebugInfo::infoSignature = infoSignature;
}

#endif // DEBUGINFO_H
