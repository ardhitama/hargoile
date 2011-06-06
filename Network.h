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

    int reqToken(QString &tokenRequestString); // forge SSK request here, always on secure connection
    int reqTokenValidity(QString &clientTokentring); // also forge token request
    int reqTokenRevocation(QString &clientTokentring);

    QString downloadRoute(QString routeId);

    virtual ~Network();

private:
    Network();
    bool isValidHeader(QString headerStr);
    QPointer<Network> network;

signals:
//    int receivedToken(QString &clientTokentring); // need a qstring placeholder
      void respTokenValidity(QString &respStr, int status); // -1 conn error, 0 header not valid, 1 success
//    int reveivedTokenRevocation(); // -1 fail, 0 cant revoke, 1 revoked

public slots:
    void replyToken(QNetworkReply *rep);
    void replyTokenValidity(QNetworkReply *rep);
    void replyTokenRevocation(QNetworkReply *rep);
};

#endif // NETWORK_H
