#ifndef RECORDERUI_H
#define RECORDERUI_H

#include "../../src/Utility/String.h"
#include "../UIAbstract.h"

class RecorderUI : virtual public UIAbstract
{
public:
    void appendPositionListView(const String &str);
    void toInitState();
    void toStoppedState();
    void toRecordingState();
    void toPausedState();
};

#endif // RECORDERUI_H
