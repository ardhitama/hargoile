#ifndef SINGLETON_H
#define SINGLETON_H

#include "../Exception/Exception.h"
#include <boost/smart_ptr.hpp>

/*
  How to use:
  Make this as base class of a class that going to be a singleton class
  Note: don't make virtual base class from this class
*/

template<typename T> class Singleton
{
public:
    static T& getInstance();
    explicit Singleton();
    virtual ~Singleton();
	
private:
    static boost::shared_ptr<T> instance;
};

// thread safe Singleton
template<class T>
T& Singleton<T>::getInstance()
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
				return *instance;
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
    return *instance;
}

template<class T>
Singleton<T>::Singleton()
{
	//
}

template<class T>
Singleton<T>::~Singleton()
{
	//delete instance;
	//instance = 0;
}

template<class T>
boost::shared_ptr<T> Singleton<T>::instance;

#endif // SINGLETON_H
