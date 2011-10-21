DEPLOYMENTFOLDERS = # file1 dir1

VERSION = 0.0.1
CONFIG += silent
symbian: {
    #TARGET.EPOCSTACKSIZE = 0x5000 // 20kb
    #TARGET.EPOCHEAPSIZE = 0x20000 0x1000000 // Min 128kb, Max 16Mb
    #TARGET.EPOCALLOWDLLDATA = 1
    TARGET.UID3 = 0xE57332A1
    TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
    TARGET = Hargoile_symb_001

    TEMPLATE = app
    CONFIG += mobility
    MOBILITY += location

    DEFINES += RELEASE
}

simulator: {
    QT += core
    QT -= gui
    TARGET.UID3 = 0xE57332A1
    TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
    TARGET = Hargoile_sim_001

    TEMPLATE = app
    CONFIG += mobility console
    MOBILITY += location

    DEFINES += DEBUG
}

QT += gui network multimedia xml

PRECOMPILED_HEADER = stdafx.h
INCLUDEPATH += ../../libs

DEFINES += QT_MOBILITY QT_APP USE_SQLITEDB

SOURCES += \
    ../../src/QtMain.cpp \
    ../../src/Application/Route.cpp \
    ../../src/Application/Hargoile.cpp \
    ../../src/Application/qt/ErrorNotificationImpl.cpp \
    ../../src/Location/qtm/PositionRecorderImpl.cpp

HEADERS += \
    ../../src/Algorithm/LineSimplification/DouglasPeucker.h \
    ../../src/Application/Storage.h \
    ../../src/Application/Route.h \
    ../../src/Application/MovementSimulator.h \
    ../../src/Application/Hargoile.h \
    ../../src/Application/ErrorNotification.h \
    ../../src/Application/config.h \
    ../../src/Application/qt/ErrorNotificationImpl.h \
    ../../src/Database/DatabaseResult.h \
    ../../src/Database/DatabaseException.h \
    ../../src/Database/DatabaseAll.h \
    ../../src/Database/Database.h \
    ../../src/Database/sqlite/DatabaseImpl.h \
    ../../src/Exception/ExceptionAll.h \
    ../../src/Exception/Exception.h \
    ../../src/Exception/DebugLog.h \
    ../../src/Exception/DebugInfo.h \
    ../../src/Exception/Assert.h \
    ../../src/Technique/Singleton.h \
    ../../src/Utility/String.h \
    ../../src/Utility/Point.h \
    ../../src/Utility/Number.h \
    ../../src/Utility/MutexLocker.h \
    ../../src/Utility/GeoPoint.h \
    ../../src/Utility/GeoCalc.h \
    ../../src/stdafx.h \
    ../../src/Location/LocationAll.h \
    ../../src/Location/qtm/LocationRecorderImpl.h \
    ../../src/Location/LocationRecorder.H \
    ../../src/Technique/TechniqueAll.h \
    ../../src/Utility/UtilityAll.h \
    ../../src/Utility/qt/MutexLockerImpl.h

FORMS +=

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../../Project.txt




























