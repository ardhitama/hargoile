#include "StateManager.h"

StateManager::StateManager()
{
    currentState = State::Invalid;
    nextState = State::Invalid;
}


StateManager& StateManager::getInstance()
{
    sync;
    static State state;
    return &state;
}

void StateManager::switchState(State newState)
{
    currentState = nextState;
    nextState = newState;
}

