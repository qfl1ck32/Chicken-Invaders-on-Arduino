#include "./SettingsLCDMenuState.h"

#include "../../globals.h"

void SettingsLCDMenuState::setup() {
    static const char *const messages[] = {"Go back", "Contrast -", "Contrast +", "Backlight -", "Backlight +"};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsLCDMenuState::goBack, SettingsLCDMenuState::decreaseContrast, SettingsLCDMenuState::increaseContrast,
                                  SettingsLCDMenuState::decreaseBacklight, SettingsLCDMenuState::increaseBacklight};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void SettingsLCDMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsLCDMenuState::cleanup() {
    joystick.clearHandlers();
}

void SettingsLCDMenuState::goBack() {
    stateManager.changeState(settingsMenuStateId);
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