#include "./SettingsLCDMenuState.h"

#include "../../globals.h"

void SettingsLCDMenuState::setup() {
    static const char cMinus[] PROGMEM = "Contrast -";
    static const char cPlus[] PROGMEM = "Contrast +";
    static const char bMinus[] PROGMEM = "Backlight -";
    static const char bPlus[] PROGMEM = "Backlight +";

    static const uint64_t image PROGMEM = 0x182424424242423c;

    static const char *const messages[] PROGMEM = {backMessage, cMinus, cPlus, bMinus, bPlus};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    char **msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {goToSettingsMenu, SettingsLCDMenuState::decreaseContrast, SettingsLCDMenuState::increaseContrast,
                                  SettingsLCDMenuState::decreaseBacklight, SettingsLCDMenuState::increaseBacklight};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t imageFromPROGMEM = readImageFromPROGMEM(&image);

    matrix->displayImage(imageFromPROGMEM);
}

void SettingsLCDMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsLCDMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void SettingsLCDMenuState::increaseContrast() {
    lcd->changeContrast(-20);
}

void SettingsLCDMenuState::decreaseContrast() {
    lcd->changeContrast(20);
}

void SettingsLCDMenuState::increaseBacklight() {
    lcd->changeBacklight(10);
}

void SettingsLCDMenuState::decreaseBacklight() {
    lcd->changeBacklight(-10);
}