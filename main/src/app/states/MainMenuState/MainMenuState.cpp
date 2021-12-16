#include "./MainMenuState.h"

#include "../../globals.h"

void MainMenuState::setup() {
    static const char play[] PROGMEM = "Play";
    static const char settings[] PROGMEM = "Settings";
    static const char leaderboard[] PROGMEM = "Leaderboard";
    static const char about[] PROGMEM = "About";

    static const char *const messages[] PROGMEM = {play, settings, leaderboard, about};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToAbout};
    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void MainMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void MainMenuState::cleanup() {
    joystick.clearHandlers();
    button.clearHandler();

    lcd->clear();
}

void MainMenuState::goToPlay() {
    stateManager.changeState(playingStateId);
}

void MainMenuState::goToSettings() {
    stateManager.changeState(settingsMenuStateId);
}

void MainMenuState::goToLeaderboard() {
    stateManager.changeState(leaderboardStateId);
}

void MainMenuState::goToAbout() {
    stateManager.changeState(aboutMenuStateId);
}