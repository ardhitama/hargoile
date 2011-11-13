#include "Json.h"

bool Json::parse(const String& jsonText)
{
    try
    {
        jsNode = libjson::parse(jsonText);
        return true;
    }
    catch(...)
    {
        throw;
    }
    return false;
}

bool Json::toBool(const String &name)
{
    JSONNode::const_iterator it = jsNode.begin();
    while (it != jsNode.end())
    {
        if (it->name() == name)
        {
            return it->as_bool();
        }
        ++it;
    }
    return 0;
}

int Json::toInt(const String &name)
{
    JSONNode::const_iterator it = jsNode.begin();
    while (it != jsNode.end())
    {
        if (it->name() == name)
        {
            return it->as_int();
        }
        ++it;
    }
    return 0;
}

double Json::toDouble(const String &name)
{
    JSONNode::const_iterator it = jsNode.begin();
    while (it != jsNode.end())
    {
        if (it->name() == name)
        {
            return it->as_float();
        }
        ++it;
    }
    return 0.0f;
}

String Json::toString(const String &name)
{
    JSONNode::const_iterator it = jsNode.begin();
    while (it != jsNode.end())
    {
        if (it->name() == name)
        {
            return it->as_float();
        }
        ++it;
    }
    return "";
}


void Json::parseJsonNode(const JSONNode &jsNode)
{
    /*
    JSONNode::const_iterator it = jsNode.begin();

    while (it != jsNode.end()){
        // recursively call ourselves to dig deeper into the tree
        if (it->type() == JSON_ARRAY || it->type() == JSON_NODE){
            parseJsonNode(*it);
        }

        // get the node name and value as a string
        std::string node_name = it->name();

        // find out where to store the values
        if (node_name == "RootA"){
            rootA = it->as_string();
        }
        else if (node_name == "ChildA"){
            childA = it->as_string();
        }
        else if (node_name == "ChildB")
            childB = it->as_int();

        //increment the iterator
        ++i;
    }
    */
}
