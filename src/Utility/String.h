#ifndef STRING_H
#define STRING_H

#include <string>
#include <cstdlib>
#include "../../libs/boost/lexical_cast.hpp"

class String : virtual public std::string
{
public:
	String() : std::string()
	{
		//
	}

	String(const char *str) : std::string(str)
	{
		//
	}

	String(const unsigned char *str) : std::string((char*)str)
	{
		//
	}

	inline String& operator = (const char *rStr)
	{
		String::assign(rStr);
		return *this;
	}

	inline String& operator = (const std::string& rStr)
	{
		String::assign(rStr);
		return *this;
	}

	inline String& operator << (const char* rStr)
	{
		String::append(rStr);
		return *this;
	}
};

inline bool operator == (const String &lStr, const char *rStr)
{
	if(lStr.compare(rStr)) // == 0, equal
		return false;
	return true;
}

inline bool operator != (const String &lStr, const char *rStr)
{
	if(lStr.compare(rStr)) // != 0, not equal
		return true;
	return false;
}

inline String& operator << (String &lStr, const String &rStr)
{
	lStr.append(rStr);
	return lStr;
}

inline String operator << (const char *lStr, const String &rStr)
{
	String ret = lStr;
	ret.append(rStr);
	return ret;
}

inline String& operator << (String &lStr, const double rNum)
{
	lStr.append(boost::lexical_cast<std::string>(rNum));
	return lStr;
}

inline String& operator << (String &lStr, const int rNum)
{
	lStr.append(boost::lexical_cast<std::string>(rNum));
	return lStr;
}

inline String& operator << (String &lStr, const long long rNum)
{
	lStr.append(boost::lexical_cast<std::string>(rNum));
	return lStr;
}

#endif // STRING_H
