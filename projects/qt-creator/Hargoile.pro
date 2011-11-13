# Qt-mobility 1.2.0 include path fix
INCLUDEPATH += C:\Qt\QtSDK\Symbian\SDKs\Symbian3Qt473\src\location

DEPLOYMENTFOLDERS = # file1 dir1

symbian: {
    #TARGET.EPOCSTACKSIZE = 0x5000 // 20kb
    #TARGET.EPOCHEAPSIZE = 0x20000 0x1000000 // Min 128kb, Max 16Mb
    #TARGET.EPOCALLOWDLLDATA = 1
    TARGET.UID3 = 0xE5A83714
    TARGET.CAPABILITY += \
        LocalServices \
        NetworkServices \
        ReadUserData \
        UserEnvironment \
        WriteUserData \
        Location

    TARGET = Hargoile_symb_001

    TEMPLATE = app
    CONFIG += mobility
    MOBILITY += location

    DEFINES += DEBUG

    #QMAKE_CXXFLAGS.GCCE -= -fvisibility-inlines-hidden
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

QT += gui network multimedia sql

#QMAKE_CXXFLAGS += -std=gnu++0x
#QMAKE_CXXFLAGS += -std=c++0x

#PRECOMPILED_HEADER = ../../src/stdafx.h
INCLUDEPATH += ../../libs/

DEFINES += TARGET_QTM USE_QSQLITEDB URI_PASS_ANSI
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
    ../../src/Location/qtm/LocationRecorder.cpp \
    ../../src/Network/qt/Http.cpp \
    ../../libs/uriparser/UriShorten.c \
    ../../libs/uriparser/UriResolve.c \
    ../../libs/uriparser/UriRecompose.c \
    ../../libs/uriparser/UriQuery.c \
    ../../libs/uriparser/UriParseBase.c \
    ../../libs/uriparser/UriParse.c \
    ../../libs/uriparser/UriNormalizeBase.c \
    ../../libs/uriparser/UriNormalize.c \
    ../../libs/uriparser/UriIp4Base.c \
    ../../libs/uriparser/UriIp4.c \
    ../../libs/uriparser/UriFile.c \
    ../../libs/uriparser/UriEscape.c \
    ../../libs/uriparser/UriCompare.c \
    ../../libs/uriparser/UriCommon.c \
    ../../libs/libjson/Source/libjson.cpp \
    ../../libs/libjson/Source/JSONWriter.cpp \
    ../../libs/libjson/Source/JSONWorker.cpp \
    ../../libs/libjson/Source/JSONValidator.cpp \
    ../../libs/libjson/Source/JSONStream.cpp \
    ../../libs/libjson/Source/JSONPreparse.cpp \
    ../../libs/libjson/Source/JSONNode_Mutex.cpp \
    ../../libs/libjson/Source/JSONNode.cpp \
    ../../libs/libjson/Source/JSONMemory.cpp \
    ../../libs/libjson/Source/JSONIterators.cpp \
    ../../libs/libjson/Source/JSONDebug.cpp \
    ../../libs/libjson/Source/JSONChildren.cpp \
    ../../libs/libjson/Source/JSONAllocator.cpp \
    ../../libs/libjson/Source/JSON_Base64.cpp \
    ../../libs/libjson/Source/internalJSONNode.cpp \
    ../../src/Application/MovementSimulator.cpp \
    ../../src/Utility/Json.cpp \
    ../../gui/qtm/RouteConfigUI.cpp

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
    ../../src/Exception/LogOutAbstract.h \
    ../../src/Exception/qt/LogOut.h \
    ../../gui/qtm/PopupUI.h \
    ../../gui/UIAbstract.h \
    ../../src/Database/qsqlite/Database.h \
    ../../src/Network/HttpAbstract.h \
    ../../src/Network/qt/Http.h \
    ../../src/Network/NetworkAll.h \
    ../../src/Utility/StringMap.h \
    ../../src/Network/HttpRequest.h \
    ../../src/Utility/ByteArray.h \
    ../../src/Network/URI.h \
    ../../libs/uriparser/UriParseBase.h \
    ../../libs/uriparser/UriNormalizeBase.h \
    ../../libs/uriparser/UriIp4Base.h \
    ../../libs/uriparser/UriIp4.h \
    ../../libs/uriparser/UriDefsUnicode.h \
    ../../libs/uriparser/UriDefsConfig.h \
    ../../libs/uriparser/UriDefsAnsi.h \
    ../../libs/uriparser/UriCommon.h \
    ../../libs/uriparser/UriBase.h \
    ../../libs/uriparser/Uri.h \
    ../../libs/libjson/libjson.h \
    ../../libs/libjson/JSONOptions.h \
    ../../libs/libjson/Source/NumberToString.h \
    ../../libs/libjson/Source/JSONWorker.h \
    ../../libs/libjson/Source/JSONValidator.h \
    ../../libs/libjson/Source/JSONStream.h \
    ../../libs/libjson/Source/JSONSingleton.h \
    ../../libs/libjson/Source/JSONPreparse.h \
    ../../libs/libjson/Source/JSONNode.h \
    ../../libs/libjson/Source/JSONMemoryPool.h \
    ../../libs/libjson/Source/JSONMemory.h \
    ../../libs/libjson/Source/JSONGlobals.h \
    ../../libs/libjson/Source/JSONDefs.h \
    ../../libs/libjson/Source/JSONDebug.h \
    ../../libs/libjson/Source/JSONChildren.h \
    ../../libs/libjson/Source/JSONAllocator.h \
    ../../libs/libjson/Source/JSON_Base64.h \
    ../../libs/libjson/Source/internalJSONNode.h \
    ../../libs/libjson/mempool++/mempool.h \
    ../../libs/libjson/Source/JSONDefs/Visual_C.h \
    ../../libs/libjson/Source/JSONDefs/Unknown_C.h \
    ../../libs/libjson/Source/JSONDefs/Strings_Defs.h \
    ../../libs/libjson/Source/JSONDefs/GNU_C.h \
    ../../src/Utility/VariantMap.h \
    ../../src/Utility/Variant.h \
    ../../src/Utility/Json.h \
    ../../gui/qtm/RouteConfigUI.h

FORMS += \
    ../../gui/qtm/RecorderUI.ui \
    ../../gui/qtm/WelcomeUI.ui \
    ../../gui/qtm/MenuUI.ui \
    ../../gui/qtm/RouteConfigUI.ui


OTHER_FILES += \
    ../../Project.txt \

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()








































































































