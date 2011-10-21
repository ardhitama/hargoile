#ifndef STDAFX_H
#define STDAFX_H

#ifdef QT_APP
#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#endif

#ifdef QT_MOBILITY
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>

// must use qt mobility namespace
QTM_USE_NAMESPACE // must the latest after any qt mobility headers
#endif // QT_MOBILITY

// Stds
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <fstream>
#include <exception>
#include <typeinfo>

// Boost
#include "../libs/boost/exception/all.hpp"
#include "../libs/boost/current_function.hpp"
#include "../libs/boost/smart_ptr.hpp"

#ifdef USE_SQLITEDB
#include "../libs/sqllite3/sqlite3.h"
#endif USE_SQLITEDB

// internals
#include "Exception/ExceptionAll.h"
#include "Technique/TechniqueAll.h"
#include "Utility/UtilityAll.h"
#include "Database/DatabaseAll.h"
#include "Location/LocationAll.h"

#endif // STDAFX_H
