#include "Authentication.h"
#include "Network.h"
#include "Storage.h"

Authentication::Authentication()
{
}

Authentication Authentication::getInstance()
{
    if(auth.isNull())
        auth = new Authentication();
    return auth;
}

bool Authentication::authenticateToken()
{
    Network
}


