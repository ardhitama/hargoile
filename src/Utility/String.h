#ifndef STRING_H
#define STRING_H

#include <string>
#include "../../libs/boost/lexical_cast.hpp"

class String : public std::string
{
public:
    String() : std::string()
    {
        //
    }

    String(const std::string &str) : std::string(str)
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

    String(int num)
    {
        String::assign(boost::lexical_cast<std::string>(num));
    }

    String(long long num)
    {
        String::assign(boost::lexical_cast<std::string>(num));
    }

    String(unsigned int num)
    {
        String::assign(boost::lexical_cast<std::string>(num));
    }

    String(unsigned long long num)
    {
        String::assign(boost::lexical_cast<std::string>(num));
    }

    String(float num)
    {
        String::assign(boost::lexical_cast<std::string>(num));
    }

    String(double num)
    {
        String::assign(boost::lexical_cast<std::string>(num));
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

    inline String& operator << (const String &rStr)
    {
        String::append(rStr);
        return *this;
    }

    inline String& operator << (const double rNum)
    {
        String::append(boost::lexical_cast<std::string>(rNum));
        return *this;
    }

    inline String& operator << (const int rNum)
    {
        String::append(boost::lexical_cast<std::string>(rNum));
        return *this;
    }

    inline String& operator << (const long long rNum)
    {
        String::append(boost::lexical_cast<std::string>(rNum));
        return *this;
    }

	inline String& operator << (const unsigned long long rNum)
    {
        String::append(boost::lexical_cast<std::string>(rNum));
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

inline String operator << (const char *lStr, const String &rStr)
{
    String ret = lStr;
    ret.append(rStr);
    return ret;
}

#endif // STRING_H
