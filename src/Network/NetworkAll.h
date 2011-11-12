#ifndef NETWORKALL_H
#define NETWORKALL_H

#include "HttpAbstract.h"
#include "HttpRequest.h"

#ifdef TARGET_QTM
#include "qt/Http.h"
#endif

#ifdef TARGET_WIN
#include "win/Http.h"
#endif

#endif // NETWORKALL_H
