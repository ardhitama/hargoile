#ifndef DATABASE_H
#define DATABASE_H

/*
  Sqlite Database Implementation
*/

#include "../../Exception/ExceptionAll.h"
#include "../../../libs/sqllite3/sqlite3.h"
#include "../../Utility/String.h"
#include "../DatabaseAll.h"

class Database : virtual public DatabaseAbstract
{
public:
    Database(const char *filePath) throw();

    virtual ~Database();

    inline int getDBStatus()
    {
        return dbStatus;
    }

    bool openDB(const char *filePath) throw();

    int coutTables() throw();

    DatabaseResult exec(const String sqlStmt);

    inline DatabaseResult operator << (const String sqlStmt)
    {
        return exec(sqlStmt);
    }

    enum { DBOk, DBNotOpen, DBNotReady };

private:
    int dbStatus, sqliteStatus;
    sqlite3 *db;
    sqlite3_stmt *dbStmt;
    String schemaName;
};

#endif // DATABASE_H
