DEPLOYMENTFOLDERS = # file1 dir1

VERSION = 0.0.1
CONFIG += silent
symbian: {
        #TARGET.EPOCSTACKSIZE = 0x5000 // 20kb
        #TARGET.EPOCHEAPSIZE = 0x20000 0x1000000 // Min 128kb, Max 16Mb
        #TARGET.EPOCALLOWDLLDATA = 1
        TARGET.UID3 = 0xE57332A1
        TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
        TARGET = Hargoile_s60v5_v001

        TEMPLATE = app
        CONFIG += mobility
        MOBILITY += location

        DEFINES += RELEASE
}

simulator: {
        TARGET.UID3 = 0xE57332A1
        TARGET.CAPABILITY += LocalServices NetworkServices ReadUserData UserEnvironment WriteUserData
        TARGET = Hargoile_s60v5_v001

        TEMPLATE = app
        CONFIG += mobility
        MOBILITY += location

        DEFINES += DEBUG
}

QT += core gui network multimedia xml

PRECOMPILED_HEADER = stdafx.h
INCLUDEPATH += ../../libs/

DEFINES += QT_MOBILITY QT_APP SQLITE_THREADSAFE=1

SOURCES += \
    ../../src/Hargoile.cpp \
    ../../dialogs/AccountLinkDlg.cpp \
    ../../src/Storage.cpp \
    ../../src/Route.cpp \
    ../../src/Network.cpp \
    ../../src/Authentication.cpp \
    ../../src/Utility.cpp \
    ../../dialogs/RecorderDlg.cpp \
    ../../dialogs/RouteDlg.cpp \
    ../../dialogs/ManagerDlg.cpp \
    ../../src/Config.cpp \
    ../../src/QtMain.cpp \
    ../../src/StateManager.cpp \
    ../../src/Exception/ErrorReporting.cpp \
    ../../src/Logger.cpp \
    ../../src/Location/qt-mobility/PositionRecorderImpl.cpp \
    ../../src/Exception/Exception.cpp
HEADERS += \
    ../../src/Hargoile.h \
    ../../dialogs/AccountLinkDlg.h \
    ../../src/Storage.h \
    ../../src/Route.h \
    ../../src/Network.h \
    ../../src/Authentication.h \
    ../../src/Utility.h \
    ../../src/stdafx.h \
    ../../dialogs/RecorderDlg.h \
    ../../dialogs/RouteDlg.h \
    ../../dialogs/ManagerDlg.h \
    ../../src/Thread.h \
    ../../src/Config.h \
    ../../src/MutexLocker.h \
    ../../src/StateManager.h \
    ../../src/Exception/Assert.h \
    ../../src/Exception/ErrorReporting.h \
    ../../src/Logger.h \
    ../../src/Exception/Exception.h \
    ../../src/Location/PositionRecorder.h \
    ../../src/Location/qt-mobility/PositionRecorderImpl.h \
    ../../src/Pattern/Singleton.h
FORMS += \
    ../../dialogs/RecorderDlg.ui \
    ../../dialogs/RouteDlg.ui \
    ../../dialogs/ManagerDlg.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../../Project.txt


















