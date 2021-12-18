#include "./WelcomeState.h"

#include "../../globals.h"

WelcomeState::WelcomeState() {
    this->delayer.updateInterval(350);
}

void WelcomeState::setup() {
    static const char welcomeMessage[] PROGMEM = "Welcome!";

    static const uint64_t icon PROGMEM = 0x00004a4a4e0a4a00;

    button.setOnStateChange(WelcomeState::moveToEnterYourNameState);

    char *welcome = readStringFromPROGMEM(welcomeMessage);
    char *pressXToContinue = readStringFromPROGMEM(pressXToContinueMessage);

    lcd->printOnRow(welcome, 0);
    lcd->printOnRow(pressXToContinue, 1);

    delete welcome;
    delete pressXToContinue;

    uint64_t image = readImageFromPROGMEM(&icon);

    matrix->displayImage(image);
}

void WelcomeState::handle() {
    if (this->delayer.canRun()) {
        lcd->scrollRow(1);
    }
}

void WelcomeState::cleanup() {
    button.clearHandler();
    lcd->clear();

    matrix->setAllLeds(false);
}

void WelcomeState::moveToEnterYourNameState() {
    stateManager.changeState<MainMenuState>();
}
