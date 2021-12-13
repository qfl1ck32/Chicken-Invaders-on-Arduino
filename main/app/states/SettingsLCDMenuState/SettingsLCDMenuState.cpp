#pragma once

#include "./SettingsLCDMenuState.h"

#include "../SettingsMenuState/SettingsMenuState.cpp"

void SettingsLCDMenuState::setup() {
    static const char *const messages[] PROGMEM = {"Go back", "Contrast -", "Contrast +", "Backlight -", "Backlight +"};

    menu->setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsLCDMenuState::goBack, SettingsLCDMenuState::decreaseContrast, SettingsLCDMenuState::increaseContrast,
                                  SettingsLCDMenuState::decreaseBacklight, SettingsLCDMenuState::increaseBacklight};

    menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick->setHandlerOnYAxisChangeUp(menuGoUp);
    joystick->setHandlerOnYAxisChangeDown(menuGoDown);

    joystick->setHandlerSwStateChange(menuSelect);
}

void SettingsLCDMenuState::handle() {
    menu->run();
    joystick->handleJoystickMovements();
}

void SettingsLCDMenuState::cleanup() {
    joystick->clearHandlers();
}

void SettingsLCDMenuState::goBack() {
    stateManager->changeState<SettingsMenuState>();
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