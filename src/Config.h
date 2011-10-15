#ifndef CONFIG_H
#define CONFIG_H

#include "stdafx.h"

class Config
{
public:
    static Config& getInstance();
    void setConfig(Config configType, String value);
    String& getToken();
private:
    Config();
    String strToken;
};

#endif // CONFIG_H
