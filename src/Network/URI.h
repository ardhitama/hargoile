#ifndef URI_H
#define URI_H

#include "../../libs/uriparser/Uri.h"
#include "../Utility/String.h"
#include "../Exception/ExceptionAll.h"

#include <vector>

class URI
{
public:

    URI()
    {
        //
    }

    URI(String strUri) throw(Exception)
    {
        try
        {
            setUri(strUri);
        }
        catch (Exception &e)
        {
            throw e;
        }
    }

    bool setUri(String strUri) throw(Exception)
    {
        UriUriA obUri;
        UriParserStateA pstUri;

        pstUri.uri = &obUri;

        if(uriParseUriA(&pstUri, strUri.data()) != URI_SUCCESS)
        {
            uriFreeUriMembersA(&obUri);
            throw Exception() << ("Invalid URI received \"" << strUri << "\"") << DebugInfo(TRACE(), DebugInfo::Error);
        }
        else
        {
            uri = strUri;
            scheme = getTextSlice(obUri.scheme.first, obUri.scheme.afterLast);
            userInfo = getTextSlice(obUri.userInfo.first, obUri.userInfo.afterLast);
            host = getTextSlice(obUri.hostText.first, obUri.hostText.afterLast);
            port = getTextSlice(obUri.portText.first, obUri.portText.afterLast);

            UriPathSegmentA *pathSgmt = obUri.pathHead;
            while(pathSgmt != 0)
            {
                path.push_back(getTextSlice(pathSgmt->text.first, pathSgmt->text.afterLast));
                pathSgmt = pathSgmt->next;
            }
            query = getTextSlice(obUri.query.first, obUri.query.afterLast);
            fragment = getTextSlice(obUri.fragment.first, obUri.fragment.afterLast);
            uriFreeUriMembersA(&obUri);
            return true;
        }
        return false;
    }



    inline String getUri()
    {
        return uri;
    }

    inline String getHost()
    {
        return host;
    }

    String getPath()
    {
        String strPath;
        for(unsigned int i=0; i<path.size(); ++i)
        {
            strPath << "/" << path[i];
        }
        return strPath;
    }

private:
    String uri, scheme, userInfo, host, port, query, fragment;
    std::vector<String> path;

    inline String getTextSlice(const char *first, const char *afterLast)
    {
        if(first != 0 && afterLast != 0)
            return String(first).substr(0, afterLast - first);
        return "";
    }

};

#endif // URI_H
