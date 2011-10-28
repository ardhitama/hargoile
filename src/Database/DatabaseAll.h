#ifndef DATABASEALL_H
#define DATABASEALL_H

#include "DatabaseException.h"
#include "DatabaseAbstract.h"
#include "DatabaseResult.h"

#ifdef USE_SQLITEDB
#include "sqlite/Database.h"
#endif

#ifdef USE_QSQLITEDB
#include "qsqlite/Database.h"
#endif

#endif // DATABASEALL_H
