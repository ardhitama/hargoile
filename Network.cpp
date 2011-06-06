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

    qurl.setUrl(serverUrlString);
    qurl.setPort(80);

    qnetreq.setUrl(qurl);
    qnetreq.setRawHeader("User-Agent", clientVersionString);

    qnetmgr.get(qnetreq);
    connect(qnetmgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyToken(QNetworkReply*)));
}

void Network::replyToken(QNetworkReply *rep)
{
}

void Network::replyTokenValidity(QNetworkReply *rep)
{
    int status = -1;
    QString respStr = "";
    if(rep->error() == QNetworkReply::NoError)
    {
        respStr = rep->readAll();
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

Network Network::getInstance()
{
    if(network.isNull())
        network = new Network();
    return network;
}
