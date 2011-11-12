#ifndef HTTP_H
#define HTTP_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "../../../libs/boost/shared_ptr.hpp"
#include "../../../libs/boost/make_shared.hpp"
#include "../HttpAbstract.h"

class Http : public QObject//, public virtual HttpAbstract
{
    Q_OBJECT
public:
    Http();
    bool post(HttpRequest& httpRequest, VariantMap& varMap);
    bool get(const String& url, VariantMap& varMap);
    bool get(const String& url, HttpRequest& httpRequest, VariantMap& varMap);

public slots:
    void onReplyFinished() throw(Exception);
    void onLoadProgress() throw(Exception);
};

#endif // HTTP_H
