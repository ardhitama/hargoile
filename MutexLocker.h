#ifndef MUTEXLOCKER_H
#define MUTEXLOCKER_H

#include "stdafx.h"

class MutexLocker
{
public:
    inline MutexLocker()
    {
#ifdef QT_APP
        qmutex.lock();
#endif
    }

    inline ~MutexLocker()
    {
#ifdef QT_APP
        qmutex.unlock();
#endif
    }

#ifdef QT_APP
    QMutex qmutex;
#endif
};

#define sync MutexLocker mutexLocker;

#endif // MUTEXLOCKER_H
