#ifndef SINGLETON_H
#define SINGLETON_H

#include "../Exception/Exception.h"

/*
  How to use:
  Make this as base class of a class that going to be a singleton class
  Note: don't make virtual base class from this class
*/

template<typename T> class Singleton
{
public:
    inline static T& getInstance()
	{
		return instance;
	}
	
private:
    static T& instance;
};

template<class T>
T& Singleton<T>::instance = T();


#endif // SINGLETON_H
