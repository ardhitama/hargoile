#ifndef STORAGE_H
#define STORAGE_H

#include "stdafx.h"
#include "Route.h"

class Storage : public QObject
{
public:
    int saveToken(QString &tokenString);
    int loadToken(QString &tokenString);

    bool saveRoute(QString name);
    Route loadRoute(QString name);
    QList listAllRoutes();

    Storage getInstance();
    virtual ~Storage();

private:
    Storage();
    QMutex saveTokenMutex;
    QPointer<Storage> storage;
};

#endif // STORAGE_H
