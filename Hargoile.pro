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
}

QT += core gui network multimedia xml

PRECOMPILED_HEADER = stdafx.h

DEFINES += VER

SOURCES += main.cpp \
    Hargoile.cpp \
    AccountLinkDlg.cpp \
    Storage.cpp \
    Route.cpp \
    Network.cpp \
    Authentication.cpp \
    Utility.cpp
HEADERS += \
    Hargoile.h \
    AccountLinkDlg.h \
    Storage.h \
    Route.h \
    Network.h \
    Authentication.h \
    Utility.h \
    stdafx.h
FORMS += \
    AccountLinkDlg.ui

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES +=
