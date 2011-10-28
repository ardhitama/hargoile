#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include "../Exception/Exception.h"

class DatabaseException : public Exception
{
public:
    DatabaseException() : Exception("Database exception has occured") {}
    DatabaseException(const String &msg) : Exception(msg) {}
};

class DatabaseOpenFailedException : public DatabaseException
{
public:
    DatabaseOpenFailedException() : DatabaseException("Can't open database file") {}
};

class DatabaseNotOpenException : public DatabaseException
{
public:
    DatabaseNotOpenException() : DatabaseException("Database not open") {}
};

class DatabaseFailException : public DatabaseException
{
public:
    DatabaseFailException() : DatabaseException("Database is fail") {}
};

class DatabaseNoSchemaSelectedException : public DatabaseException
{
public:
    DatabaseNoSchemaSelectedException() : DatabaseException("Database doesn't have active schema") {}
};

class DatabaseStatementInvalidException : public DatabaseException
{
public:
    DatabaseStatementInvalidException() : DatabaseException("Database query statement is invalid") {}
};

class DatabaseResultNotDoneException : public DatabaseException
{
public:
    DatabaseResultNotDoneException() : DatabaseException("Database is returned an error while processing the query results") {}
};

#endif // DATABASEEXCEPTION_H
