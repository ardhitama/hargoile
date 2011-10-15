#ifdef USE_SQLITEDB
#ifndef DATABASEIMPL_H
#define DATABASEIMPL_H

/*
  Sqlite Database Implementation
*/

#include "../../libs/sqllite3/sqlite3.h"
#include "../../Utility/String.h"
#include "../Database.h"
#include "../DatabaseResult.h"
#include "../DatabaseException.h"

class DatabaseImpl : virtual public Database
{
public:
    DatabaseImpl(const char *filePath) throw(...)
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

    virtual ~DatabaseImpl()
    {
        sqlite3_close(db);
    }

    inline int getDBStatus()
    {
        return dbStatus;
    }

    bool openDB(const char *filePath) throw(...)
    {
        sqliteStatus = sqlite3_open_v2(filePath, &db,  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, 0);
        if(sqliteStatus == SQLITE_ERROR)
        {
            sqlite3_close(db);
            throw DatabaseOpenFailedException() << DebugInfo(TRACE, DebugInfo::Error);
            return false;
        }
        dbStatus = DBOk;
        return true;
    }

    int coutTables() throw(...)
    {
        if(dbStatus != SQLITE_OK)
            throw DatabaseNotOpenException() << DebugInfo(TRACE, DebugInfo::Error);

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
            tableCount = res.getRowData().at(0).getColumn().at(0).getIntData();

        } catch (...)
        {
            throw;
        }

        return tableCount;
    }

    DatabaseResult exec(const String sqlStmt)
    {
        if(sqliteStatus != SQLITE_OK)
            throw DatabaseNotOpenException() << DebugInfo(TRACE, DebugInfo::Error);

		sqliteStatus = sqlite3_prepare_v2(db, sqlStmt.data(),
                                          -1, &dbStmt, NULL);
        if(sqliteStatus != SQLITE_OK)
            throw DatabaseStatementInvalidException() << " " << sqlite3_errmsg(db) << DebugInfo(TRACE, DebugInfo::Error);

        int iCol = 0, colType = -1;
        int colCount = sqlite3_column_count(dbStmt);
        int stepRet = sqlite3_step(dbStmt);

        DatabaseColumn dbCol;
        DatabaseRow dbRow;
        DatabaseResult dbRes;

        while(stepRet == SQLITE_ROW)
        {
            for(iCol=0; iCol<colCount; ++iCol)
            {
                colType = sqlite3_column_type(dbStmt, iCol);
                if(colType == SQLITE_INTEGER)
                {
                    dbCol = DatabaseColumn(sqlite3_column_int(dbStmt, iCol));
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
            throw DatabaseResultNotDoneException() << " " << sqlite3_errmsg(db) << DebugInfo(TRACE, DebugInfo::Error);

        return dbRes;
    }

    enum { DBOk, DBNotOpen, DBNotReady };

private:
    int dbStatus, sqliteStatus;
    sqlite3 *db;
    sqlite3_stmt *dbStmt;
    String schemaName;


};

#endif // DATABASEIMPL_H
#endif // USE_SQLITEDB
