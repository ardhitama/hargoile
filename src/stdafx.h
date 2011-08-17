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
#include <string>
#include <memory>
#include <fstream>
#include <exception>
using namespace std;

#include "Assert.h"

const string sServerUrl = "127.0.0.1/hargoile/";
const string sClientName = "Hargoile_s60v5_v001";
const string sConfigFilename = "hargoile.cfg";

#endif // STDAFX_H
