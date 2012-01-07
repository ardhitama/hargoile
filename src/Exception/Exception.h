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

	inline String getInfo()
	{
		return strInfo;
	}

	inline DebugInfo getDebugInfo()
	{
		return dbgInfo;
	}

	inline Exception& operator << (const String &strInfo)
	{
		Exception::strInfo.append(strInfo);
		return *this;
	}

	inline Exception& operator << (const char *strInfo)
	{
		Exception::strInfo.append(strInfo);
		return *this;
	}

	inline Exception& operator << (const DebugInfo &dbgInfo)
	{
		Exception::dbgInfo = dbgInfo;
		DebugLog::getInstance().add(dbgInfo);
		return *this;
	}

private:
	String strInfo; // user friendly message
	DebugInfo dbgInfo; // info for debugging purpose
};

#endif // EXCEPTION_H
