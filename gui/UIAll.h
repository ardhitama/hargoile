#ifndef UIALL_H
#define UIALL_H

#ifdef TARGET_QTM
#include "qtm/WelcomeUI.h"
#include "qtm/RecorderUI.h"
#include "qtm/MenuUI.h"
#include "qtm/PopupUI.h"
#include "qtm/RouteConfigUI.h"
#include "qtm/RetryUI.h"
#endif // TARGET_QTM

#ifdef TARGET_WIN
#include "win/WelcomeUI.h"
#include "win/RecorderUI.h"
#include "win/MenuUI.h"
#include "win/PopupUI.h"
#include "win/RouteConfigUI.h"
#include "win/RetryUI.h"
#endif // TARGET_WIN

#endif // UIALL_H
