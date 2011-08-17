#ifndef UTILITY_H
#define UTILITY_H

#include "stdafx.h"

class Utility : public QObject
{
public:
    Utility();
    virtual ~Utility();
    void forgeSSKRequest(string clientSSK, string *SSKRequest);
};

#endif // UTILITY_H
