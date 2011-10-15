#ifndef STRING_H
#define STRING_H

#include <string>
#include <cstdlib>

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

	inline void operator << (const String &apdStr)
	{
		String::append(apdStr);
	}

	inline void operator = (const char *rStr)
	{
		String::assign(rStr);
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

#endif // STRING_H
