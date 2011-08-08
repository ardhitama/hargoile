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

DEFINES += QT_MOBILITY QT_APP SQLITE_THREADSAFE

SOURCES += \
    Hargoile.cpp \
    dialogs/AccountLinkDlg.cpp \
    Storage.cpp \
    Route.cpp \
    Network.cpp \
    Authentication.cpp \
    Utility.cpp \
    Recorder.cpp \
    dialogs/RecorderDlg.cpp \
    dialogs/RouteDlg.cpp \
    dialogs/ManagerDlg.cpp \
    Config.cpp \
    QtMain.cpp \
    StateManager.cpp \
    libs/sqllite3/sqlite3.c
HEADERS += \
    Hargoile.h \
    dialogs/AccountLinkDlg.h \
    Storage.h \
    Route.h \
    Network.h \
    Authentication.h \
    Utility.h \
    stdafx.h \
    Recorder.h \
    dialogs/RecorderDlg.h \
    dialogs/RouteDlg.h \
    dialogs/ManagerDlg.h \
    Thread.h \
    Config.h \
    MutexLocker.h \
    StateManager.h \
    Assert.h \
    libs/sqllite3/sqlite3ext.h \
    libs/sqllite3/sqlite3.h
FORMS += \
    dialogs/RecorderDlg.ui \
    dialogs/RouteDlg.ui \
    dialogs/ManagerDlg.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES +=
