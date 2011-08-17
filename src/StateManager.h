#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "stdafx.h"
#include "MutexLocker.h"

class StateManager
{
public:
    enum State{ Invalid = 0, Idle, Init,
                LingkingAccount, UnlinkingAccount, LinkingError, UnlinkingError,
                Recording, RecordingPaused, RecordingStopped, RecordingError,
                UploadingRoute, DownloadingRoute, UploadingError, DownloadingError };

    static StateManager& getInstance();
    StateManager getCurrentState();
    void switchState(State newState);

private:
    State currentState, nextState;
    StateManager();
};

#endif // STATEMANAGER_H
