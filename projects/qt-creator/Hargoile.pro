# Qt-mobility 1.2.0 include path fix
INCLUDEPATH += C:\Qt\QtSDK\Symbian\SDKs\Symbian3Qt473\src\location

DEPLOYMENTFOLDERS = # file1 dir1

symbian: {
    #TARGET.EPOCSTACKSIZE = 0x5000 // 20kb
    #TARGET.EPOCHEAPSIZE = 0x20000 0x1000000 // Min 128kb, Max 16Mb
    #TARGET.EPOCALLOWDLLDATA = 1
    TARGET.UID3 = 0xE5A83714
    TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
    TARGET = Hargoile_symb_001

    #TEMPLATE = app
    CONFIG += mobility
    MOBILITY += location

    DEFINES += DEBUG
}
simulator: {
    # QT += core
    # QT -= gui
    TARGET.UID3 = 0xE5A83714
    TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
    TARGET = Hargoile_sim_001

    TEMPLATE = app
    CONFIG += mobility
    MOBILITY += location

    DEFINES += DEBUG
}

QT += gui network multimedia

#QMAKE_CXXFLAGS += -std=gnu++0x
#QMAKE_CXXFLAGS += -std=c++0x

PRECOMPILED_HEADER = ../../src/stdafx.h
INCLUDEPATH += ../../libs/

DEFINES += USE_SQLITEDB TARGET_QTM
# Fix for QT conflict
# DEFINES += QT_NO_DEBUG_STREAM QT_NO_DATASTREAM

SOURCES += \
    ../../src/QtMain.cpp \
    ../../src/Application/Route.cpp \
    ../../src/Application/Hargoile.cpp \
    ../../gui/qtm/WelcomeUI.cpp \
    ../../gui/qtm/RecorderUI.cpp \
    ../../gui/qtm/MenuUI.cpp \
    ../../src/Application/Storage.cpp \
    ../../gui/qtm/PopupUI.cpp \
    ../../libs/sqllite3/sqlite3.c

HEADERS += \
    ../../src/Algorithm/LineSimplification/DouglasPeucker.h \
    ../../src/Application/Storage.h \
    ../../src/Application/Route.h \
    ../../src/Application/MovementSimulator.h \
    ../../src/Application/Hargoile.h \
    ../../src/Application/config.h \
    ../../src/Database/DatabaseResult.h \
    ../../src/Database/DatabaseException.h \
    ../../src/Database/DatabaseAll.h \
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
    ../../src/Technique/TechniqueAll.h \
    ../../src/Utility/UtilityAll.h \
    ../../src/Utility/qt/MutexLockerImpl.h \
    ../../gui/UIAll.h \
    ../../gui/qtm/WelcomeUI.h \
    ../../gui/qtm/RecorderUI.h \
    ../../gui/qtm/MenuUI.h \
    ../../src/Location/qtm/LocationRecorder.h \
    ../../src/Location/LocationRecorderAbstract.h \
    ../../src/Database/DatabaseAbstract.h \
    ../../src/Database/sqlite/Database.h \
    ../../src/Exception/LogOutAbstract.h \
    ../../src/Exception/qt/LogOut.h \
    ../../gui/qtm/PopupUI.h \
    ../../libs/sqllite3/sqlite3.h

FORMS += \
    ../../gui/qtm/RecorderUI.ui \
    ../../gui/qtm/WelcomeUI.ui \
    ../../gui/qtm/MenuUI.ui


OTHER_FILES += \
    ../../Project.txt \

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()









































