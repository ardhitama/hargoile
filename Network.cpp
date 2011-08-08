#include "Network.h"

Network::Network()
{
    //
}

void Network::reqTokenValidity()
{
    QNetworkAccessManager qnetmgr(this);
    QNetworkRequest qnetreq;

    QUrl qurl;

    qurl.setUrl(serverUrlString.append("asktokenvalidity"));
    qurl.setPort(80);

    qnetreq.setUrl(qurl);
    qnetreq.setRawHeader("User-Agent", clientVersionString);

    qnetmgr.get(qnetreq);
    connect(qnetmgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyTokenValidity(QNetworkReply*)));
}

void Network::replyToken(QNetworkReply *rep)
{
}

void Network::replyTokenValidity(QNetworkReply &rep)
{
    int status = -1;
    string respStr = "";
    QList<string> repStack = respStr.split('\n');
    if(rep.error() == QNetworkReply::NoError)
    {
        respStr = rep.readAll();
        qDebug << respStr;
        status = 1;
    }
    else
    {
        status = -1;
    }
    emit respTokenValidity(respStr, status);
}

void Network::replyTokenRevocation(QNetworkReply *rep)
{
}

Network& Network::getInstance()
{
    static Network network;
    return &network;
}
