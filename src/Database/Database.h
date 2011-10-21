#ifndef DATABASE_H
#define DATABASE_H

#include "../Utility/String.h"
#include "DatabaseResult.h"

class Database
{
public:
	/*
	Database();
    Database(char const *filePath);

    // true: db open success
    bool openDB(char const *filePath) throw(...);
    
    bool changeSchema(char const &schemaName) throw(...);

    // true: db is empty
    bool isEmpty();
	*/

	virtual DatabaseResult exec(const String sqlStmt) = 0;
	virtual DatabaseResult operator << (const String sqlStmt) = 0;

protected:
    int dbStatus;
};

#endif // DATABASE_H
