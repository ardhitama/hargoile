#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

class Exception : virtual std::exception
{
public:
    friend void operator<< (Exception &ex, std::string strInfo);
private:
    std::string strInfo;
};

void operator << (Exception &ex, std::string &strInfo)
{
    ex.strInfo += strInfo;
}

#endif // EXCEPTION_H
