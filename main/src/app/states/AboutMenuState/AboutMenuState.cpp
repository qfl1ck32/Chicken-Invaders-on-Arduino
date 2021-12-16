#include "./AboutMenuState.h"

#include "../../globals.h"

void AboutMenuState::setup() {
    // FIXME PROGMEM
    static const char* const messages[] PROGMEM = {
        "Back",
        "App Name: Invaders",
        "Programmer: Rusu Andrei-Cristian",
        "Github: https://github.com/qfl1ck32/Invaders-on-Arduino",
    };

    menu.setMessages(messages, sizeof(messages) / sizeof(char*));

    HandlerFunction handlers[] = {AboutMenuState::goBack};
    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.clearHandlers();
    button.clearHandler();

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void AboutMenuState::handle() {
    menu.run(true);
    joystick.handleJoystickMovements();
}

void AboutMenuState::cleanup() {
    joystick.clearHandlers();
    button.clearHandler();

    lcd->clear();
}

void AboutMenuState::goBack() {
    stateManager.changeState(mainMenuStateId);
    ;
}
