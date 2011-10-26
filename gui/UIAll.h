#ifndef UIALL_H
#define UIALL_H

#ifdef TARGET_QTM
#include "qtm/WelcomeUI.h"
#include "qtm/RecorderUI.h"
#include "qtm/MenuUI.h"
#include "qtm/PopupUI.h"
#endif // TARGET_QTM

#ifdef TARGET_WIN
#include "win/WelcomeUI.h"
#include "win/RecorderUI.h"
#include "win/MenuUI.h"
#include "win/PopupUI.h"
#endif // TARGET_WIN

#endif // UIALL_H
