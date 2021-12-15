#include "./StateManager.h"

void StateManager::addState(State *state) {
    this->states[this->numberOfStates] = state;

    ++this->numberOfStates;
}

void StateManager::handle() {
    if (!this->currentState) return;

    this->currentState->handle();
}

void StateManager::changeState(byte stateId) {
    if (this->currentState != 0) {
        this->currentState->cleanup();
    }

    for (int i = 0; i < this->numberOfStates; ++i) {
        if (stateId == this->states[i]->id) {
            this->currentState = this->states[i];
            break;
        }
    }

    this->currentState->setup();
}