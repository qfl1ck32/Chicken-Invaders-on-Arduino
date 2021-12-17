#include "./WelcomeState.h"

#include "../../globals.h"

void WelcomeState::setup() {
    button.setOnStateChange(WelcomeState::moveToEnterYourNameState);

    static const char welcomeMessage[] PROGMEM = "Welcome!";

    char welcome[9];

    char pressXToContinue[21];

    // readFromPROGMEM(pressXToContinueMessage, pressXToContinue, 20);
    // readFromPROGMEM(welcomeMessage, welcome, 8);

    lcd->printOnRow(welcome, 0);
    lcd->printOnRow(pressXToContinue, 1);
}

void WelcomeState::handle() {
    if (this->delayer.canRun()) {
        lcd->scrollRow(1);
    }
}

void WelcomeState::cleanup() {
    button.clearHandler();
    lcd->clear();
}

void WelcomeState::moveToEnterYourNameState() {
    stateManager.changeState(mainMenuStateId);
}
