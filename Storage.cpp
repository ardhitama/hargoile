#include "Storage.h"
#include "Network.h"

Storage::Storage()
{
}

/*
  int Storage::loadToken(QString &tokenString);
  return:
  -1 : fs fail
  0  : token not available
  1  : token loaded
*/
int Storage::loadToken(QString &tokenString)
{
    QScopedPointer<QFile> file = new QFile("tkn.hgl");

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    QByteArray tokenLine = file.readLine(); //
    file->close();
    if(tokenLine.size() < 40)
        return 0;

    tokenString.clear();
    tokenString.append(tokenLine);

    return 1;
}

int Storage::saveToken(QString &tokenString)
{
    QMutexLocker(&saveTokenMutex);

    if(tokenString.size() < 40)
        return 0;

    QScopedPointer<QFile> file = new QFile("tkn.hgl");

    if (!file->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        return -1;

    file->write(tokenString);
    file->close();

    return 1;
}

bool Storage::saveRoute(QString name)
{
}

bool Storage::loadRoute(QString name)
{
}

QList Storage::listAllRoutes()
{
}

Storage Storage::getInstance()
{
    if(storage.isNull())
        storage = new Storage();
    return storage;
}
