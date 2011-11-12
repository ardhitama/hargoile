#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <map>
#include <vector>

#include "../Utility/String.h"
#include "../Utility/StringMap.h"
#include "../Utility/ByteArray.h"
#include "../Utility/Number.h"

#include "URI.h"

class HttpBinData
{
public:
    HttpBinData() {}
    HttpBinData(const String& filename, const std::vector<unsigned char>& binData)
    {
        setFilename(filename);
        setBinData(binData);
    }

    const String& getFilename()
    {
        return filename;
    }

    const String getBinData()
    {
        return std::string(data.begin(), data.end());
    }

    void setFilename(const String& filename)
    {
        HttpBinData::filename = filename;
    }

    void setBinData(const std::vector<unsigned char>& binData)
    {
        HttpBinData::data = binData;
    }

private:
    String filename;
    std::vector<unsigned char> data;
};

class HttpBinDataMap : public std::map<String, HttpBinData>
{
public:
    void add(const String& name, const HttpBinData& binData)
    {
        std::pair<String, HttpBinData> inPair = std::pair<String, HttpBinData>(name, binData);
        insert(inPair);
    }
};

// only one file post supported
class HttpRequest
{
public:
    HttpRequest(const String& url)
    {
        uri.setUri(url);

        headerBoundary << "-----" << hgl::rangedRand(2343243, 9999999) << hgl::rangedRand(7343, 52342);

        headerMap.add("POST", uri.getPath() << " HTTP/1.1");
        headerMap.add("Host", uri.getHost());
        headerMap.add("Connection", "keep-alive");
        headerMap.add("User-Agent", "Hargoile Mobile");
        headerMap.add("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
        headerMap.add("Accept-Encoding", "gzip,deflate,sdch");
        headerMap.add("Accept-Language", "id-ID,id;q=0.8,en-US;q=0.6,en;q=0.4");
        headerMap.add("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.3");
        headerMap.add("Content-Type", "multipart/form-data, boundary=" << headerBoundary);
    }

    inline void addFormField(const String& name, const String& value)
    {
        fieldMap.add(name, value);
    }

    inline void addRawHeader(const String& name, const String& value)
    {
        headerMap.add(name, value);
    }

    void addDataField(const String& name, const HttpBinData& binData)
    {
        binDataMap.add(name, binData);
    }

    inline const StringMap& getHeaderMap()
    {
        return headerMap;
    }

    inline const StringMap& getFieldMap()
    {
        return fieldMap;
    }

    inline const HttpBinDataMap& getBinDataMap()
    {
        return binDataMap;
    }

    String getPostContentRequest()
    {
        String postContent;

        for(StringMap::iterator it=fieldMap.begin(); it!=fieldMap.end(); ++it)
        {
            std::pair<String, String> fieldPair = *it;
            postContent << "--" << headerBoundary << "\r\n";
            postContent << "content-disposition: form-data; name=\"" << fieldPair.first <<"\"\r\n\r\n";
            postContent << fieldPair.second << "\r\n";
        }

        for(HttpBinDataMap::iterator it=binDataMap.begin(); it!=binDataMap.end(); ++it)
        {
            std::pair<String, HttpBinData> fieldPair = *it;
            postContent << "--" << headerBoundary << "\r\n";
            postContent << "content-disposition: form-data; name=\"" << fieldPair.first <<"\"; filename=\"" << fieldPair.second.getFilename() << "\"\r\n\r\n";
            postContent << fieldPair.second.getBinData() << "\r\n";
        }

        /*
        postContent << "--" << headerBoundary << "\r\n";
        postContent << "content-disposition: form-data; name=\"file\"; filename=\"file.txt\"\r\n";
        postContent << "Content-Type: application/octet-stream\r\n\r\n";
        postContent << formData << "\r\n";
        */

        postContent << "--" << headerBoundary << "--\r\n";

        headerMap.add("Content-Length", (int)postContent.size());
        return postContent;
    }

    String getUri()
    {
        return uri.getUri();
    }

private:
    StringMap headerMap;
    StringMap fieldMap;
    HttpBinDataMap binDataMap;
    String headerBoundary;
    URI uri;

    inline void recalculateContentLength()
    {

    }
};


#endif // HTTPREQUEST_H
