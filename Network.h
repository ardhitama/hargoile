#ifndef NETWORK_H
#define NETWORK_H

#include "stdafx.h"

/*
  Non-blocking Network request / response
*/
class Network : public QObject
{
public:
    Network getInstance();

    int requestToken(QString &tokenRequestString); // forge SSK request here, always on secure connection
    int requestTokenValidity(QString &clientTokentring); // also forge token request
    int requestTokenRevocation(QString &clientTokentring);

    QString downloadRoute(QString routeId);

    virtual ~Network();

private:
    Network();
    QPointer<Network> network;

signals:
//    int receivedToken(QString &clientTokentring); // need a qstring placeholder
//    int receivedTokenValidity(); // -1 fail, 0 not valid, 1 valid
//    int reveivedTokenRevocation(); // -1 fail, 0 cant revoke, 1 revoked

public slots:
    void replyToken(QNetworkReply *rep);
    void replyTokenValidity(QNetworkReply *rep);
    void replyTokenRevocation(QNetworkReply *rep);
};

#endif // NETWORK_H
