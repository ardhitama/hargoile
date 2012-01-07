#ifndef VARIANT_H
#define VARIANT_H

#include "../../libs/boost/any.hpp"
#include "String.h"

class Variant : public boost::any
{
public:
    Variant(boost::any val) : boost::any(val) {}
    inline String toString()
    {
        return boost::any_cast<String>(*this);
    }

    inline int toInt()
    {
        return boost::any_cast<int>(*this);
    }

    inline double toDouble()
    {
        return boost::any_cast<double>(*this);
    }
};

#endif // VARIANT_H
