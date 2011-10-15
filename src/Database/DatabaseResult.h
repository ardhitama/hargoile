#ifndef DATABASERESULT_H
#define DATABASERESULT_H

#include <vector>
#include "../Utility/String.h"

class DatabaseColumn
{
public:

	DatabaseColumn(const int intData)
	{
		setIntData(intData);
	}

	DatabaseColumn(const long long int64Data)
	{
		setInt64Data(int64Data);
	}

	DatabaseColumn(const double doubleData)
	{
		setDoubleData(doubleData);
	}

	DatabaseColumn(const String &strData)
	{
		setStrData(strData);
	}

	DatabaseColumn(const unsigned char *binData)
	{
		setBinData(binData);
	}

	DatabaseColumn(const unsigned char &&binData)
	{
		setBinData(&binData);
	}

	DatabaseColumn(const bool isNull)
	{
		if(isNull)
			setNullData();
	}

	DatabaseColumn()
	{
		//
	}

	void setIntData(const int intData)
	{
		DatabaseColumn::intData = intData;
		DatabaseColumn::colType = TYPE_INTEGER;
	}

	void setInt64Data(const long long int64Data)
	{
		DatabaseColumn::int64Data = int64Data;
		DatabaseColumn::colType = TYPE_BIGINTEGER;
	}

	void setDoubleData(const double doubleData)
	{
		DatabaseColumn::doubleData = doubleData;
		DatabaseColumn::colType = TYPE_FLOAT;
	}

	void setStrData(const String &strData)
	{
		DatabaseColumn::strData = strData;
		DatabaseColumn::colType = TYPE_TEXT;
	}

	void setBinData(const unsigned char *binData)
	{
		int dtLen = sizeof(binData);
		DatabaseColumn::binData.clear();
		DatabaseColumn::binData.resize(dtLen);
		std::copy(binData, binData + dtLen, &DatabaseColumn::binData[0]);
		DatabaseColumn::colType = TYPE_BLOB;
	}

	void setBinData(const unsigned char &&binData)
	{
		int dtLen = sizeof(binData);
		DatabaseColumn::binData.clear();
		DatabaseColumn::binData.resize(dtLen);
		DatabaseColumn::binData.at(0) = std::move(binData);
		DatabaseColumn::colType = TYPE_BLOB;
	}

	void setNullData()
	{
		DatabaseColumn::isNullData = true;
		DatabaseColumn::colType = TYPE_NULL;
	}

	bool getNullData()
	{
		return isNullData;
	}

	int getIntData()
	{
		return intData;
	}

	long long getInt64Data()
	{
		return int64Data;
	}

	String getStrData()
	{
		return strData;
	}

	double getDoubleData()
	{
		return doubleData;
	}

	std::vector<unsigned char> getBinData()
	{
		return binData;
	}

	int getColType()
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
};

class DatabaseRow
{
public:
	void addColumn(const DatabaseColumn &column)
	{
		DatabaseRow::column.push_back(column);
	}

	std::vector<DatabaseColumn>& getColumn()
	{
		return column;
	}
private:
	std::vector<DatabaseColumn> column;
	int colCount, rowNum;
};

class DatabaseResult
{
public:

	void addRowData(DatabaseRow rowData)
	{
		DatabaseResult::rowData.push_back(rowData);
	}

	std::vector<DatabaseRow>& getRowData()
	{
		return rowData;
	}

private:
	std::vector<DatabaseRow> rowData;
	int rowCount;
};


#endif // DATABASERESULT_H
