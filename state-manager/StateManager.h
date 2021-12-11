#pragma once

#include "../state/State.h"

#define MAX_STATES 12

class StateManager {
   public:
    short numberOfStates;

    State *states[MAX_STATES];

    StateManager() {
        this->numberOfStates = 0;
    }

    short currentState = -1;

    void addState(State *);

    void addStates(State *[], int);

    void changeState(short);
    void handle();
};

void StateManager::addState(State *state) {
    this->states[this->numberOfStates] = state;

    ++this->numberOfStates;
}

void StateManager::addStates(State *states[], int numberOfStates) {
    for (int i = 0; i < numberOfStates; ++i) {
        this->states[this->numberOfStates + i] = states[i];
    }

    this->numberOfStates += numberOfStates;
}

void StateManager::handle() {
    if (this->currentState == -1) return;

    for (int i = 0; i < this->numberOfStates; ++i) {
        if (this->currentState == this->states[i]->state) {
            this->states[i]->handle();
            return;
        }
    }
}

void StateManager::changeState(short state) {
    if (this->currentState != -1) {
        for (int i = 0; i < this->numberOfStates; ++i) {
            if (this->currentState == this->states[i]->state) {
                this->states[i]->cleanup();
                break;
            }
        }
    }

    this->currentState = state;

    for (int i = 0; i < this->numberOfStates; ++i) {
        if (state == this->states[i]->state) {
            this->states[i]->setup();
            return;
        }
    }
}
