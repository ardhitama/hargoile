#ifndef STRING_H
#define STRING_H

#include <string>

class String : virtual public std::string
{
public:
    String();
    String(char *str);
    void operator << (String &apdStr);
    void operator = (char &rStr);
};

String::String() : std::string("")
{
    //
}

String::String(char *str) : std::string(str)
{
    //
}

inline void String::operator << (String &apdStr)
{
    String::append(apdStr);
}

inline void String::operator = (char &rStr)
{
    String::assign(&rStr);
}

#endif // STRING_H
