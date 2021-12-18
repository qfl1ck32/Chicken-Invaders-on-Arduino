#include "./WelcomeState.h"

#include "../../globals.h"

WelcomeState::WelcomeState() {
    this->delayer.updateInterval(350);
}

void WelcomeState::setup() {
    button.setOnStateChange(WelcomeState::moveToEnterYourNameState);
    static const char welcomeMessage[] PROGMEM = "Welcome!";

    char *welcome = readStringFromPROGMEM(welcomeMessage);
    char *pressXToContinue = readStringFromPROGMEM(pressXToContinueMessage);

    lcd->printOnRow(welcome, 0);
    lcd->printOnRow(pressXToContinue, 1);

    delete welcome;
    delete pressXToContinue;
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
