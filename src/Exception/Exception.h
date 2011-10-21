#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <list>
#include <exception>
#include "DebugLog.h"
#include "DebugInfo.h"
#include "../Utility/String.h"

class Exception : virtual public std::exception
{
public:

	Exception()
	{
		Exception::strInfo = String();
	}

	Exception(const String &strInfo)
	{
		Exception::strInfo = strInfo;
	}

	Exception(const char *strInfo)
	{
		Exception::strInfo = String(strInfo);
	}

	Exception(const DebugInfo &dbgInfo)
	{
		Exception::dbgInfo = dbgInfo;
		DebugLog::getInstance().add(dbgInfo);
	}

	Exception(const String &strInfo, const DebugInfo &dbgInfo)
	{
		Exception::strInfo = strInfo;
		Exception::dbgInfo = dbgInfo;
		DebugLog::getInstance().add(dbgInfo);
	}

	virtual ~Exception() throw()
	{
		//
	}

	String getInfo()
	{
		return strInfo;
	}

	DebugInfo getDebugInfo()
	{
		return dbgInfo;
	}

	friend Exception& operator << (Exception &ex, const String &strInfo);
	friend Exception& operator << (Exception &ex, const char *strInfo);
	friend Exception& operator << (Exception &ex, const DebugInfo &dbgInfo);

private:
	String strInfo; // user friendly message
	DebugInfo dbgInfo; // info for debugging purpose
};

inline Exception& operator << (Exception &ex, const String &strInfo)
{
	ex.strInfo.append(strInfo);
	return ex;
}

inline Exception& operator << (Exception &ex, const char *strInfo)
{
	ex.strInfo.append(String(strInfo));
	return ex;
}

inline Exception& operator << (Exception &ex, const DebugInfo &dbgInfo)
{
	ex.dbgInfo = dbgInfo;
	DebugLog::getInstance().add(dbgInfo);
	return ex;
}

#endif // EXCEPTION_H
