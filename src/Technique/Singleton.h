#ifndef SINGLETON_H
#define SINGLETON_H

#include "../Exception/Exception.h"
#include <boost/smart_ptr.hpp>

/*
  How to use:
  Make this as base class of a class that going to be a singleton class
  Note: don't make virtual base class from this class
*/

template<class T> class Singleton
{
public:
    static T* getInstance();
    explicit Singleton();
    virtual ~Singleton();
private:
    static boost::shared_ptr<T> instance;
};

// thread safe Singleton
template<class T>
T* Singleton<T>::getInstance()
{
    static int refCount = 0;
    static bool isInstantiated = false;

    ++refCount;
    if(isInstantiated == false)
    {
        if(refCount == 1)
        {
            try
            {
                instance = boost::shared_ptr<T>(new T());
                isInstantiated = true;
                refCount = 0;
                return instance.get();
            } catch(...)
            {
                // rethrow any exceptions
                throw;
            }
        }
        else
        {

        }
    }
    --refCount;
    return instance.get();
}

#endif // SINGLETON_H
