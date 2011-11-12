#ifndef DATABASE_H
#define DATABASE_H

/*
  Sqlite Database Implementation
*/

#include "../../Exception/ExceptionAll.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QVariant>
#include "../../Utility/String.h"
#include "../DatabaseAll.h"

class Database : virtual public DatabaseAbstract
{
public:
    Database(const String& filePath) throw()
    {
        dbStatus = DB_NOT_OPEN;
        sqliteStatus = -1;

        try
        {
            openDB(filePath);
        }
        catch(...)
        {
            throw;
        }
    }

    virtual ~Database()
    {
        db.close();
    }

    inline int getDBStatus()
    {
        return dbStatus;
    }

    bool openDB(const String& filePath) throw()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");

        #ifdef Q_OS_LINUX
        // NOTE: We have to store database file into user home folder in Linux
        QString path(QDir::home().path());
        path.append(QDir::separator()).append(filePath);
        path = QDir::toNativeSeparators(path);
        db.setDatabaseName(path);
        #else
        // NOTE: File exists in the application private folder, in Symbian Qt implementation
        db.setDatabaseName(filePath.data());
        #endif

        sqliteStatus = db.open();
        if(sqliteStatus == false)
        {
            db.close();
            dbStatus = DB_NOT_OPEN;
            sqlError = db.lastError();
            throw DatabaseOpenFailedException() << DebugInfo("\"" << sqlError.text().toStdString() << "\"\n" << TRACE(), DebugInfo::Error);
            return false;
        }
        dbStatus = DB_OK;
        return true;
    }

    int coutTables() throw()
    {
        if(dbStatus != DB_OK)
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

    DatabaseResult exec(const String sqlStmt)
    {
        DatabaseColumn dbCol;
        DatabaseRow dbRow;
        DatabaseResult dbRes;

        if(dbStatus != DB_OK)
            throw DatabaseNotOpenException() << DebugInfo(TRACE(), DebugInfo::Error);

        QSqlQuery query;
        sqliteStatus = query.exec(sqlStmt.data());
        sqlError = db.lastError();
        if(sqliteStatus == false)
            throw DatabaseStatementInvalidException() << DebugInfo(String(sqlStmt) << "\n\"" << sqlError.text().toStdString() << "\"\n" << TRACE(), DebugInfo::Error);

        int colType = -1;
        QSqlRecord sqlRecord = query.record();
        int colCount = sqlRecord.count();
        int isSelect = query.isSelect();
        bool isNoResult = true;

        if(isSelect == true)
            isNoResult = false;

        while(query.next())
        {
            for(int iCol=0; iCol<colCount; ++iCol)
            {
                colType = query.value(iCol).type();
                if(colType == QVariant::Int)
                {
                    dbCol = DatabaseColumn(query.value(iCol).toInt());
                    dbCol.setInt64Data(query.value(iCol).toInt());
                }
                else if(colType == QVariant::Double)
                {
                    dbCol = DatabaseColumn(query.value(iCol).toDouble());
                }
                else if(colType == QVariant::String)
                {
                    dbCol = DatabaseColumn(query.value(iCol).toString().toStdString());
                }
                else if(colType == QVariant::ByteArray)
                {
                    dbCol = DatabaseColumn((unsigned char*)query.value(iCol).toByteArray().data());
                }
                else if(query.isNull(iCol))
                {
                    dbCol = DatabaseColumn(true);
                }
                dbRow.addColumn(dbCol);
            }
            dbRes.addRowData(dbRow);
            dbRow = DatabaseRow();
        }

        // query.clear(); don't need this, query is local variable

        sqlError = db.lastError();
        //@todo: bug, caused exception to be thrown when debuglog instance is not ready
        //if(query.isActive())
            //throw DatabaseResultNotDoneException() << DebugInfo(String(sqlError.text().toStdString()) << TRACE(), DebugInfo::Error);

        if(isNoResult == true)
            dbRes.setRowChanged(query.numRowsAffected());

        return dbRes;
    }

    inline DatabaseResult operator << (const String sqlStmt)
    {
        return exec(sqlStmt);
    }



private:
    int dbStatus, sqliteStatus;
    QSqlDatabase db;
    String schemaName;
    QSqlError sqlError;
};

#endif // DATABASE_H
