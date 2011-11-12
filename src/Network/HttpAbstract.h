#ifndef HTTPABSTRACT_H
#define HTTPABSTRACT_H

#include "../Utility/String.h"
#include "../Utility/VariantMap.h"
#include "../Exception/Exception.h"

#include "HttpRequest.h"

class HttpAbstract
{
public:
    virtual void post(const HttpRequest& httpRequest, VariantMap varMap = VariantMap()) = 0;
    virtual void get(const String& url, VariantMap varMap = VariantMap()) = 0;
    virtual void get(const String& url, const HttpRequest& httpRequest, VariantMap varMap = VariantMap()) = 0;

    virtual void onReplyFinished() = 0;
};

#endif // HTTPABSTRACT_H
