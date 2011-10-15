#ifndef MUTEXLOCKER_H
#define MUTEXLOCKER_H


class MutexLocker
{
private:
    explicit MutexLocker() = 0;
    explicit virtual ~MutexLocker() = 0;
};

#endif // MUTEXLOCKER_H
