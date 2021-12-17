#ifndef StateManager_h
#define StateManager_h

#include "../state/State.h"
#include "Arduino.h"

#define MAX_STATES 4

class StateManager {
   public:
    int8_t numberOfStates;

    State *states[MAX_STATES];

    State *currentState;

    StateManager() {
        this->currentState = 0;
        this->numberOfStates = 0;
    }

    void addState(State *);

    void changeState(int8_t);

    void handle();
};

#endif