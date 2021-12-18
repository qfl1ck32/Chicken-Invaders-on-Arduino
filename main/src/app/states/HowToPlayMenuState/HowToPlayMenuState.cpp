#include "./HowToPlayMenuState.h"

#include "../../globals.h"

void HowToPlayMenuState::setup() {
    static const char m1[] PROGMEM = "Have fun!";

    static const char *const messages[] PROGMEM = {backMessage, m1};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    static const uint64_t hammerImage PROGMEM = 0x00e7bd8181ff1818;

    char **msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {SettingsMenuState::goBack};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&hammerImage);

    matrix->displayImage(image);
}

void HowToPlayMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void HowToPlayMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void HowToPlayMenuState::goBack() {
    stateManager.changeState<MainMenuState>();
}
