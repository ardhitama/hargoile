#ifndef HTTPABSTRACT_H
#define HTTPABSTRACT_H

#include "../Utility/String.h"
#include "../Utility/VariantMap.h"
#include "../Exception/Exception.h"

#include "HttpRequest.h"

class HttpAbstract
{
public:
    virtual bool post(HttpRequest& /*httpRequest*/, VariantMap& /*varMap*/) throw(Exception) { return false; }
    virtual bool get(const String& /*url*/, VariantMap& /*varMap*/) { return false; }
    virtual bool get(const String& /*url*/, HttpRequest& /*httpRequest*/, VariantMap& /*varMap*/) { return false; }

	virtual void onReplyFinished() {}
	virtual void onLoadProgress() {}
};

#endif // HTTPABSTRACT_H
