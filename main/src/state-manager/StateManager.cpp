#include "./StateManager.h"

template <class S>
void StateManager::changeState() {
    if (this->currentState != 0) {
        this->currentState->cleanup();
        delete this->currentState;
    }

    this->currentState = new S();

    this->currentState->setup();
}

void StateManager::handle() {
    if (!this->currentState) return;

    this->currentState->handle();
}
