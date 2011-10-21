#ifndef DATABASEALL_H
#define DATABASEALL_H

#include "DatabaseException.h"
#include "Database.h"
#include "DatabaseResult.h"

#ifdef USE_SQLITEDB
#include "sqlite/DatabaseImpl.h"
#endif

#endif // DATABASEALL_H
