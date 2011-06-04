#include "Network.h"

Network::Network()
{
    //
}

int Network::requestTokenValidity(QString &clientTokentring)
{
    QNetworkAccessManager qnetmgr;
    QNetworkRequest qnetreq;

    QUrl qurl;

    qurl.setUrl(serverUrlString);
    qurl.setPort(80);

    qnetreq.setUrl(qurl);
    qnetreq.setRawHeader("User-Agent", clientVersionString);

    QPointer<QNetworkReply> qnetrep;
    qnetrep = qnetmgr.get(qnetreq);
    connect(qnet, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyToken(QNetworkReply*)));

    qnet->get(req);
    qnet-

    return 1;
}

void Network::replyToken(QNetworkReply *rep)
{
}

void Network::replyTokenValidity(QNetworkReply *rep)
{
    rep->
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

