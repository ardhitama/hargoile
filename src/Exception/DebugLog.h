#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <list>
#include "Assert.h"
#include "DebugInfo.h"
#include "../Utility/String.h"
#include "../Technique/Singleton.h"

class DebugLog : public Singleton<DebugLog>
{
public:
	inline void operator += (const DebugInfo &dbgInfo)
	{
		DebugLog::dbgLog.push_front(dbgInfo);
	}

	inline void add(const DebugInfo &dbgInfo)
	{
		DebugLog::dbgLog.push_front(dbgInfo);
	}
private:
	std::list<DebugInfo> dbgLog;
};



#endif // DEBUGLOG_H
