#include "./MainMenuState.h"

#include "../../globals.h"

void MainMenuState::setup() {
    static const char play[] PROGMEM = "Play";
    static const char settings[] PROGMEM = "Settings";
    static const char leaderboard[] PROGMEM = "Leaderboard";
    static const char about[] PROGMEM = "About";

    static const char *const messages[] PROGMEM = {play, settings, leaderboard, about};

    static const uint64_t mainImage PROGMEM = 0x004c424242024c00;

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToAbout};
    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&mainImage);

    matrix->displayImage(image);
}

void MainMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void MainMenuState::cleanup() {
    joystick.clearHandlers();
    button.clearHandler();

    lcd->clear();

    matrix->setAllLeds(false);
}

void MainMenuState::goToPlay() {
    stateManager.changeState<PlayingState>();
}

void MainMenuState::goToSettings() {
    stateManager.changeState<SettingsMenuState>();
}

void MainMenuState::goToLeaderboard() {
    stateManager.changeState<LeaderboardState>();
}

void MainMenuState::goToAbout() {
    stateManager.changeState<AboutMenuState>();
}
