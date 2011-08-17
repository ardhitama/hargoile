#ifndef NETWORK_H
#define NETWORK_H

#include "stdafx.h"

/*
  Non-blocking Network request / response
*/
class Network : public QObject
{
public:
    static Network& getInstance();

    int reqToken(string &tokenRequestString); // forge SSK request here, always on secure connection
    int reqTokenValidity(string &clientTokentring); // also forge token request
    int reqTokenRevocation(string &clientTokentring);

    string downloadRoute(string routeId);

    virtual ~Network();

private:
    Network();
    bool isValidHeader(string headerStr);

signals:
//    int receivedToken(string &clientTokentring); // need a string placeholder
      void respTokenValidity(string &respStr, int status); // -1 conn error, 0 header not valid, 1 success
//    int reveivedTokenRevocation(); // -1 fail, 0 cant revoke, 1 revoked

public slots:
    void replyToken(QNetworkReply &rep);
    void replyTokenValidity(QNetworkReply &rep);
    void replyTokenRevocation(QNetworkReply &rep);
};

#endif // NETWORK_H
