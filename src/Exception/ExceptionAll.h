#ifndef EXCEPTIONALL_H
#define EXCEPTIONALL_H

#include "Assert.h"
#include "DebugInfo.h"
#include "Exception.h"
#include "DebugLog.h"

#include "LogOutAbstract.h"

#ifdef TARGET_QTM
#include "qt/LogOut.h"
#endif // TARGET_QTM

#ifdef TARGET_WIN
#include "win/LogOut.h"
#endif // TARGET_WIN

#endif // EXCEPTIONALL_H
