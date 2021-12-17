#ifndef StateManager_h
#define StateManager_h

#include "../state/State.h"

class StateManager {
   public:
    State *currentState;

    StateManager() {
        this->currentState = 0;
    }

    template <class S>
    void changeState();

    void handle();
};

template <class S>
void StateManager::changeState() {
    if (this->currentState != 0) {
        this->currentState->cleanup();
        delete this->currentState;
    }

    this->currentState = new S();

    this->currentState->setup();
}

#endif