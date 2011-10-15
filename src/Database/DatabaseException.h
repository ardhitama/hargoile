#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include "../Exception/Exception.h"

class DatabaseOpenFailedException : public Exception
{
public:
	DatabaseOpenFailedException() : Exception("Can't open database file.") {}
};

class DatabaseNotOpenException : public Exception
{
public:
	DatabaseNotOpenException() : Exception("Database not Open.") {}
};

class DatabaseNoSchemaSelectedException : public Exception
{
public:
	DatabaseNoSchemaSelectedException() : Exception("Database doesn't have active schema.") {}
};

class DatabaseStatementInvalidException : public Exception
{
public:
	DatabaseStatementInvalidException() : Exception("Database query statement is invalid.") {}
};

class DatabaseResultNotDoneException : public Exception
{
public:
	DatabaseResultNotDoneException() : Exception("Database is returned an error while processing the query results.") {}
};

#endif // DATABASEEXCEPTION_H
