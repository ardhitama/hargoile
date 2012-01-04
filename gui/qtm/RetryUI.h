#ifndef RETRYUI_H
#define RETRYUI_H

#include "../../src/Utility/String.h"
#include <QMessageBox>

class RetryUI
{
public:
    static bool show(const String &strMsg)
    {
        int ret = QMessageBox::question(0, "Information", strMsg.data(), QMessageBox::Yes, QMessageBox::No, QMessageBox::Yes);
        if(ret == QMessageBox::Yes)
            return true;
        else
            return false;
    }
};

#endif // RETRYUI_H
