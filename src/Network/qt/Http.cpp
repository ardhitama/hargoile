#include "Http.h"
#include <QUrl>
#include <QEventLoop>

Http::Http()
{
}

void Http::onReplyFinished()
{
    QNetworkReply *netReply = qobject_cast<QNetworkReply *>(sender());
    int httpStatus = netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    String httpResponse = String(netReply->readAll().data());
    String httpError = netReply->errorString().toStdString();

    LogOut::error(httpResponse);
}

void Http::onLoadProgress()
{
    //
}

bool Http::post(HttpRequest& httpRequest, VariantMap& varMap) throw(Exception)
{
    try
    {
        QUrl url(QString(httpRequest.getUri().data()));
        QNetworkRequest netRequest(url);

        //String content;
        for(StringMap::const_iterator it=httpRequest.getHeaderMap().begin(); it!=httpRequest.getHeaderMap().end(); ++it)
        {
            std::pair<String, String> headerPair = *it;
            netRequest.setRawHeader(headerPair.first.data(), headerPair.second.data());
            //content << headerPair.first << ": " << netRequest.rawHeader(headerPair.first.data()).data() << "\r\n";
        }

        //content << httpRequest.getPostContentRequest();
        //LogOut::error(content);

        boost::shared_ptr<QNetworkAccessManager> netManager = boost::make_shared<QNetworkAccessManager>(this);
        //netManager = boost::make_shared<QNetworkAccessManager>(this);
        boost::shared_ptr<QNetworkReply> netReply;
        boost::shared_ptr<QEventLoop> postEvent = boost::make_shared<QEventLoop>(this);

        netReply.reset(netManager->post(netRequest, QByteArray(httpRequest.getPostContentRequest().data(), httpRequest.getPostContentRequest().size())));
        connect(netManager.get(), SIGNAL(finished(QNetworkReply*)), postEvent.get(), SLOT(quit()));
        postEvent->exec();
        //connect(netReply.get(), SIGNAL(finished()), this, SLOT(onReplyFinished()));

        int httpStatus = netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        String httpResponse = netReply->readAll().data();
        String httpError = netReply->errorString().toStdString();

        LogOut::error(httpResponse);

        varMap.add("http_status", httpStatus);
        varMap.add("http_response", httpResponse);
        varMap.add("http_error", httpError);

        if(httpStatus == 200) // OK
        {
            return true;
        }
        else if(httpStatus >= 300) // Error
        {
            throw Exception(String("HTTP Response Error (") << httpStatus << ")") << DebugInfo(httpError << httpResponse << TRACE(), DebugInfo::Error);
            return false;
        }

    } catch(Exception &ex)
    {
        throw ex;
        return false;
    }
    return false;
}

bool Http::get(const String& url, VariantMap& varMap)
{
    try
    {
        QNetworkRequest netRequest(QString(url.data()));

        boost::shared_ptr<QNetworkAccessManager> netManager = boost::make_shared<QNetworkAccessManager>(this);
        boost::shared_ptr<QNetworkReply> netReply;

        boost::shared_ptr<QEventLoop> getEvent = boost::make_shared<QEventLoop>(this);

        netReply.reset(netManager->get(netRequest));
        connect(netReply.get(), SIGNAL(finished()), getEvent.get(), SLOT(quit()));
        getEvent->exec();

        varMap.add("http_status", netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
        varMap.add("http_response", String(netReply->readAll().data()));
        varMap.add("http_error", netReply->errorString().toStdString());

    } catch(Exception &ex)
    {
        throw ex;
        return false;
    }
    return true;
}

bool Http::get(const String& url, HttpRequest& param, VariantMap& varMap)
{
    return false;
}
