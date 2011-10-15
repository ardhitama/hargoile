#pragma once

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
#endif

// Stds
#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <fstream>
#include <exception>
#include <typeinfo>

// Boost
#include "boost/exception/all.hpp"
#include "boost/current_function.hpp"
#include "boost/smart_ptr.hpp"

// built-in
#include "Assert.h"
#include "Exception/Exception.h"
#include "Pattern/Singleton.h"
#include "Utility/String.h"

#define serverUrl = "127.0.0.1/hargoile/";
#define clientName = "Hargoile_S3_v001";
#define configFilename = "hargoile.cfg";

#endif // STDAFX_H
