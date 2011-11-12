#ifndef HTTP_H
#define HTTP_H

#include "../HttpAbstract.h"

class Http 
{
public:
    Http();
    void post(HttpRequest& httpRequest);
    void get(const String& url);
    void get(const String& url, HttpRequest& httpRequest);

    void onReplyFinished();

};

#endif // HTTP_H
