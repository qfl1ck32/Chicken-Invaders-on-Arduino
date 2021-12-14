#include "./WelcomeState.h"

#include <avr/pgmspace.h>

#include "../../globals.h"

void WelcomeState::setup() {
    button.setOnStateChange(WelcomeState::moveToEnterYourNameState);

    static const char *const pressXToContinue PROGMEM = "Press X to continue";

    static const char *const welcome PROGMEM = "Welcome!";

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
    stateManager.changeState<MainMenuState>();
}
