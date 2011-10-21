#ifndef MUTEXLOCKERIMPL_H
#define MUTEXLOCKERIMPL_H

#include "../MutexLocker.h"
#include <QMutex>

#ifdef QT_APP

class QtMutexLockerImpl : public MutexLocker
{
public:
    inline QtMutexLockerImpl()
    {
        qmutex.lock();
    }

    inline ~QtMutexLockerImpl()
    {
        qmutex.unlock();
    }
    QMutex qmutex;
};

#define sync QtMutexLockerImpl qtMutexLockerImpl;

#endif // QT_APP
#endif // MUTEXLOCKERIMPL_H
