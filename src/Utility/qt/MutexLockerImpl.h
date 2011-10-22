#ifndef MUTEXLOCKERIMPL_H
#define MUTEXLOCKERIMPL_H

#include "../MutexLocker.h"
#include <QMutex>

class MutexLockerImpl : public MutexLocker
{
public:
	inline MutexLockerImpl()
    {
        qmutex.lock();
    }

	inline ~MutexLockerImpl()
    {
        qmutex.unlock();
    }
    QMutex qmutex;
};

#define sync MutexLockerImpl mutexLockerImpl;

#endif // MUTEXLOCKERIMPL_H
