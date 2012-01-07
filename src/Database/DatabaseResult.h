#ifndef DATABASERESULT_H
#define DATABASERESULT_H

#include <vector>
#include <memory>
#include <algorithm>
#include "../Utility/String.h"

#include "DatabaseAll.h"

class DatabaseColumn
{
    friend class Database;
public:
    inline bool getNullData()
    {
        return isNullData;
    }

    inline int getIntData()
    {
        return intData;
    }

    inline long long getInt64Data()
    {
        return int64Data;
    }

    inline String& getStrData()
    {
        return strData;
    }

    inline double getDoubleData()
    {
        return doubleData;
    }

    inline std::vector<unsigned char>& getBinData()
    {
        return binData;
    }

    inline int getColType()
    {
        return colType;
    }

    enum {TYPE_INTEGER, TYPE_BIGINTEGER, TYPE_TEXT, TYPE_BLOB, TYPE_FLOAT, TYPE_NULL};

private:
    int intData, colNum, colType;
    long long int64Data;
    double doubleData;
    bool isNullData;
    String strData;

    std::vector<unsigned char> binData;

    DatabaseColumn()
    {
        intData = ~0;
        colNum = 0;
        colType = -1;
        int64Data = ~0;
        doubleData = ~0;
        setNullData();
    }

    DatabaseColumn(const int intData)
    {
        setIntData(intData);
        colNum = 0;
        colType = -1;
        int64Data = ~0;
        doubleData = ~0;
        isNullData = false;
    }

    DatabaseColumn(const long long int64Data)
    {
        setInt64Data(int64Data);
        intData = ~0;
        colNum = 0;
        colType = -1;
        doubleData = ~0;
        isNullData = false;
    }

    DatabaseColumn(const double doubleData)
    {
        setDoubleData(doubleData);
        intData = ~0;
        colNum = 0;
        colType = -1;
        int64Data = ~0;
        isNullData = false;
    }

    DatabaseColumn(const String &strData)
    {
        setStrData(strData);
        intData = ~0;
        colNum = 0;
        colType = -1;
        int64Data = ~0;
        doubleData = ~0;
        isNullData = false;
    }

    DatabaseColumn(const unsigned char *binData, const int length)
    {
        setBinData(binData, length);
        intData = ~0;
        colNum = 0;
        colType = -1;
        int64Data = ~0;
        doubleData = ~0;
        isNullData = false;
    }

    /*
 DatabaseColumn(const unsigned char &&binData)
 {
  setBinData(&binData);
  intData = ~0;
  colNum = 0;
  colType = -1;
  int64Data = ~0;
  doubleData = ~0;
  isNullData = false;
 }
 */

    inline void setIntData(const int intData)
    {
        DatabaseColumn::intData = intData;
        DatabaseColumn::colType = TYPE_INTEGER;
    }

    inline void setInt64Data(const long long int64Data)
    {
        DatabaseColumn::int64Data = int64Data;
        DatabaseColumn::colType = TYPE_BIGINTEGER;
    }

    inline void setDoubleData(const double doubleData)
    {
        DatabaseColumn::doubleData = doubleData;
        DatabaseColumn::colType = TYPE_FLOAT;
    }

    inline void setStrData(const String &strData)
    {
        DatabaseColumn::strData = strData;
        DatabaseColumn::colType = TYPE_TEXT;
    }

    void setBinData(const unsigned char *binData, const int length)
    {
        DatabaseColumn::binData.clear();
        DatabaseColumn::binData.resize(length);
        if(binData != 0)
            std::copy(binData, binData + length, &DatabaseColumn::binData[0]);
        DatabaseColumn::colType = TYPE_BLOB;
    }

    /*
 void setBinData(const unsigned char &&binData)
 {
  int dtLen = sizeof(binData);
  DatabaseColumn::binData.clear();
  DatabaseColumn::binData.resize(dtLen);
  DatabaseColumn::binData.at(0) = std::move(binData);
  DatabaseColumn::colType = TYPE_BLOB;
 }
 */

    inline void setNullData()
    {
        DatabaseColumn::isNullData = true;
        DatabaseColumn::colType = TYPE_NULL;
    }
};

class DatabaseRow
{
    friend class Database;
    friend class DatabaseImpl;
public:
    inline std::vector<DatabaseColumn>& getColumnData()
    {
        return colData;
    }
private:
    std::vector<DatabaseColumn> colData;

    inline void addColumn(const DatabaseColumn &column)
    {
        DatabaseRow::colData.push_back(column);
    }
};

class DatabaseResult
{
    friend class Database;
    friend class DatabaseImpl;
public:
    inline std::vector<DatabaseRow>& getRowData()
    {
        return rowData;
    }

    inline int getRowCount()
    {
        return rowData.size();
    }

    inline int getColCount()
    {
        return rowData[0].getColumnData().size();
    }

    inline int getRowChanged()
    {
        return rowChanged;
    }

    inline DatabaseResult()
    {
        rowChanged = 0;
    }

private:
    std::vector<DatabaseRow> rowData;
    int rowChanged;

    inline void addRowData(DatabaseRow row)
    {
        DatabaseResult::rowData.push_back(row);
    }

    inline void setRowChanged(int nChg)
    {
        rowChanged = nChg;
    }
};


#endif // DATABASERESULT_H
