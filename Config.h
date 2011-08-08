#ifndef CONFIG_H
#define CONFIG_H

#include "stdafx.h"

class Config
{
public:
    static Config& getInstance();
    void setConfig(Config configType, string value);
    string getToken();
private:
    Config();
    string strToken;
};

#endif // CONFIG_H
