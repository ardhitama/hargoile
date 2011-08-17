#include "Config.h"
#include "MutexLocker.h"
#include "Storage.h"

Config::Config()
{
    strToken.clear();
}

Config& Config::getInstance()
{
    static Config config;
    return config;
}

string Config::getToken()
{
    Storage::getInstance().loadToken(strToken);
    return strToken;
}
