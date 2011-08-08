#include "Storage.h"
#include "Network.h"
#include "MutexLocker.h"

using namespace std;
Storage::Storage()
{
}

/*
  int Storage::loadToken(string &tokenString);
  return:
  -1 : fs fail
  0  : token not available
  1  : token loaded
*/
int Storage::loadToken(string &tokenString)
{
    sync;
    fstream file("tkn.hgl", fstream::in);

    if (!file.is_open())
    {
        TRACE("tkn.hgl is not found");
        return -1;
    }

    string strToken;
    file.getline((char*)strToken.data(), 2048);
    file.close();
    if(strToken.size() < 40)
    {
        TRACE("Token file is empty");
        return 0;
    }

    tokenString.assign(strToken.data());

    return 1;
}

int Storage::saveToken(string &tokenString)
{
    sync;

    if(tokenString.size() < 40)
        return 0;

    fstream file("tkn.hgl", fstream::out);

    if (!file.is_open())
    {
        TRACE("Unable to write tkn.hgl");
        return -1;
    }

    file.write(tokenString.data(), tokenString.size());
    file.close();

    return 1;
}

bool Storage::saveRoute(string &name, Route &route)
{
    sync;

    if(tokenString.size() < 40)
        return 0;

    fstream file("tkn.hgl", fstream::out);

    if (!file.is_open())
    {
        TRACE("Unable to write tkn.hgl");
        return -1;
    }

    file.write(tokenString.data(), tokenString.size());
    file.close();

    return true;
}

bool Storage::loadRoute(string &name, Route &route)
{
    return false;
}

bool Storage::listAvailableRoutes(list<string> &lstName)
{
    return true;
}

Storage& Storage::getInstance()
{
    //sync;
    //static Storage storage;
    //return &storage;
}
