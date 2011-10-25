#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include "../Utility/String.h"

class DebugInfo
{
public:
	enum {Log = 0, Notice, Warning, Error};

	DebugInfo()
	{
		DebugInfo::strInfo = String("");
		DebugInfo::infoPriority = DebugInfo::Log;
		DebugInfo::infoSignature = -1;
	}

        DebugInfo(const char *strInfo, int infoPriority = DebugInfo::Log, int infoSignature = -1)
	{
		DebugInfo::strInfo = String(strInfo);
		DebugInfo::infoPriority = infoPriority;
		DebugInfo::infoSignature = infoSignature;
	}

	DebugInfo(const String &strInfo, int infoPriority = DebugInfo::Log, int infoSignature = -1)
	{
		DebugInfo::strInfo = strInfo;
		DebugInfo::infoPriority = infoPriority;
		DebugInfo::infoSignature = infoSignature;
	}

	String getStrInfo()
	{
		return strInfo;
	}

private:
	String strInfo;
	int infoSignature;
	int infoPriority;
};

#endif // DEBUGINFO_H
