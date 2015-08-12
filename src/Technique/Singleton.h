#ifndef SINGLETON_H
#define SINGLETON_H

/*
  How to use:
  Make this as base class of a class that going to be a singleton class
  Note: don't make virtual base class from this class
*/

template<class T> class Singleton
{
public:
    static T& getInstance()
    {
        static T instance;
        return instance;
    }
};

#endif // SINGLETON_H
