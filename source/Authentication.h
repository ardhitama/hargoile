#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "stdafx.h"

class Authentication : public QObject
{
public:
    Authentication getInstance();
    int authenticateToken();
    int createToken(string username, string password);
    int revokeToken();
private:
    Authentication();
    virtual ~Authentication();
    QPointer<Authentication> auth;
};

#endif // AUTHENTICATION_H
