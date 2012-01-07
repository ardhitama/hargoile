#ifndef VARIANTMAP_H
#define VARIANTMAP_H

#include "String.h"
#include "Variant.h"
#include <map>

class VariantMap : private std::map<String, Variant>
{
public:
    void add(const String& name, const boost::any& value)
    {
        std::pair<String, Variant> pair = std::pair<String, Variant>(name,  value);
        std::pair<VariantMap::const_iterator, bool> inPair = insert(pair);
        if(inPair.second == false)
        {
            erase(pair.first);
            insert(pair);
        }
    }

    void add(const String& name, const int value)
    {
        std::pair<String, Variant> pair = std::pair<String, Variant>(name,  boost::any(value));
        std::pair<VariantMap::const_iterator, bool> inPair = insert(pair);
        if(inPair.second == false)
        {
            erase(pair.first);
            insert(pair);
        }
    }

    inline Variant& get(const String& name)
    {
        return find(name)->second;
    }
};

#endif // VARIANTMAP_H
