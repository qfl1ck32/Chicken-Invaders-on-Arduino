#include "../state/State.h"

#ifndef StateManager_h
#define StateManager_h

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

#endif