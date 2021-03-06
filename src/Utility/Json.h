#ifndef JSON_H
#define JSON_H

#include "../../libs/libjson/libjson.h"
#include "String.h"

class Json
{
public:
    bool parse(const String& jsonText);

    bool toBool(const String &name);
    int toInt(const String &name);
    double toDouble(const String &name);

    String toString(const String &name);

private:
    JSONNODE *jsNode;

    void parseJsonNode(const JSONNODE *jsNode);
};

#endif // JSON_H
