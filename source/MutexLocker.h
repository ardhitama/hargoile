#ifndef MUTEXLOCKER_H
#define MUTEXLOCKER_H

#include "stdafx.h"

#ifndef QT_APP
#error "Please make sure that we have QMutex implementation equivalent!"
#endif

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
