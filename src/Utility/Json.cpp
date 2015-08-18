#include "Json.h"

bool Json::parse(const String& jsonText)
{
    try
    {
        jsNode = json_parse(jsonText.c_str());
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
    JSONNODE_ITERATOR it = json_begin(jsNode);
    while (it != json_end(jsNode))
    {
        if (json_name(it) == name)
        {
            return json_as_bool(it);
        }
        ++it;
    }
    return 0;
}

int Json::toInt(const String &name)
{
    JSONNODE_ITERATOR it = json_begin(jsNode);
    while (it != json_end(jsNode))
    {
        if (json_name(it) == name)
        {
            return json_as_int(it);
        }
        ++it;
    }
    return 0;
}

double Json::toDouble(const String &name)
{
    JSONNODE_ITERATOR it = json_begin(jsNode);
    while (it != json_end(jsNode))
    {
        if (json_name(it) == name)
        {
            return json_as_float(it);
        }
        ++it;
    }
    return 0.0f;
}

String Json::toString(const String &name)
{
    JSONNODE_ITERATOR it = json_begin(jsNode);
    while (it != json_end(jsNode))
    {
        if (json_name(it) == name)
        {
            return json_as_float(it);
        }
        ++it;
    }
    return "";
}


void Json::parseJsonNode(const JSONNODE *jsNode)
{
    /*
    JSONNode::const_iterator it = jsNode.begin();

    while (it != json_end(jsNode)){
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
