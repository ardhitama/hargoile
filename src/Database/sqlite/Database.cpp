/*
Sqlite Database Implementation
*/

#include "Database.h"

Database::Database(const char *filePath) throw()
{
	dbStatus = DBNotOpen;
	sqliteStatus = SQLITE_ERROR;

	try
	{
		openDB(filePath);
	}
	catch(...)
	{
		throw;
	}
}

Database::~Database()
{
	sqlite3_close(db);
}


bool Database::openDB(const char *filePath) throw()
{
	sqliteStatus = sqlite3_open_v2(filePath, &db,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, 0);
	if(sqliteStatus == SQLITE_ERROR)
	{
		sqlite3_close(db);
		throw DatabaseOpenFailedException() << DebugInfo(TRACE(), DebugInfo::Error);
		return false;
	}
	dbStatus = DBOk;
	return true;
}

int Database::coutTables() throw()
{
	if(dbStatus != SQLITE_OK)
		throw DatabaseNotOpenException() << DebugInfo(TRACE(), DebugInfo::Error);

	DatabaseResult res;
	int tableCount = -1;

	try
	{
		res = exec("SELECT COUNT(name) FROM ("
			"SELECT name FROM sqlite_master "
			"WHERE type IN ('table','view') AND name NOT LIKE 'sqlite_%' "
			"UNION ALL "
			"SELECT name FROM sqlite_temp_master "
			"WHERE type IN ('table','view') )");
		tableCount = res.getRowData().at(0).getColumnData().at(0).getIntData();

	} catch (...)
	{
		throw;
	}

	return tableCount;
}

DatabaseResult Database::exec(const String sqlStmt)
{
	DatabaseColumn dbCol;
	DatabaseRow dbRow;
	DatabaseResult dbRes;

	if(sqliteStatus != SQLITE_OK)
		throw DatabaseNotOpenException() << DebugInfo(TRACE(), DebugInfo::Error);

	sqliteStatus = sqlite3_prepare_v2(db, sqlStmt.data(),
		-1, &dbStmt, NULL);
	if(sqliteStatus != SQLITE_OK)
		throw DatabaseStatementInvalidException() << DebugInfo(String(sqlStmt) << "\n\"" << sqlite3_errmsg(db) << "\"\n" << TRACE(), DebugInfo::Error);

	int iCol = 0, colType = -1;
	int colCount = sqlite3_column_count(dbStmt);
	int stepRet = sqlite3_step(dbStmt);
	bool isNoResult = true;



	if(stepRet == SQLITE_ROW)
		isNoResult = false;

	while(stepRet == SQLITE_ROW)
	{
		for(iCol=0; iCol<colCount; ++iCol)
		{
			colType = sqlite3_column_type(dbStmt, iCol);
			if(colType == SQLITE_INTEGER)
			{
				dbCol = DatabaseColumn(sqlite3_column_int(dbStmt, iCol));
				dbCol.setInt64Data(sqlite3_column_int64(dbStmt, iCol));
			}
			else if(colType == SQLITE_FLOAT)
			{
				dbCol = DatabaseColumn(sqlite3_column_double(dbStmt, iCol));
			}
			else if(colType == SQLITE_TEXT)
			{
				dbCol = DatabaseColumn(String(sqlite3_column_text(dbStmt, iCol)));
			}
			else if(colType == SQLITE_BLOB)
			{
				dbCol = DatabaseColumn((unsigned char*)sqlite3_column_blob(dbStmt, iCol));
			}
			else if(colType == SQLITE_NULL)
			{
				dbCol = DatabaseColumn(true);
			}
			dbRow.addColumn(dbCol);
		}
		dbRes.addRowData(dbRow);
		dbRow = DatabaseRow();
		stepRet = sqlite3_step(dbStmt);
	}

	sqlite3_finalize(dbStmt);

	if(stepRet != SQLITE_DONE)
		throw DatabaseResultNotDoneException() << DebugInfo(sqlite3_errmsg(db) << TRACE(), DebugInfo::Error);

	if(isNoResult == true)
		dbRes.setRowChanged(sqlite3_changes(db));

	return dbRes;
}

