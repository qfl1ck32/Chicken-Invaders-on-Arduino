#include "./StateManager.h"

void StateManager::handle() {
    if (!this->currentState) return;

    this->currentState->handle();
}
