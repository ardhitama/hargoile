#ifndef STRINGMAP_H
#define STRINGMAP_H

#include <map>
#include "String.h"

class StringMap : public std::map<String, String>
{
public:
    void add(const String& name, const String& value)
    {
        std::pair<StringMap::iterator, bool> inRet = insert(std::pair<String, String>(name, value));
        if(inRet.second == false)
        {
            erase(inRet.first);
            insert(std::pair<String, String>(name, value));
        }
    }

    String& get(const String& name)
    {
        return find(name)->second;
    }
};

#endif // STRINGMAP_H
