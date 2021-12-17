#include "./WelcomeState.h"

#include "../../globals.h"

WelcomeState::WelcomeState() {
    this->delayer.updateInterval(350);
}

void WelcomeState::setup() {
    button.setOnStateChange(WelcomeState::moveToEnterYourNameState);

    // FIXME: add PROGMEM
    static const char welcomeMessage[] = "Welcome!";

    lcd->printOnRow(welcomeMessage, 0);
    // lcd->printOnRow(pressXToContinue, 1);
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
