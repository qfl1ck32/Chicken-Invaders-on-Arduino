#include "./MainMenuState.h"

#include "../../globals.h"

void MainMenuState::setup() {
    static const char play[] PROGMEM = "Play";
    static const char settings[] PROGMEM = "Settings";
    static const char leaderboard[] PROGMEM = "Leaderboard";
    static const char howToPlay[] PROGMEM = "How to play";
    static const char about[] PROGMEM = "About";

    static const char *const messages[] PROGMEM = {play, settings, leaderboard, howToPlay, about};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    static const uint64_t mainImage PROGMEM = 0x00007e007e007e00;

    char **msgs = readArrayOfStringsFromPROGMEM(messages, sizeof(messages) / sizeof(char *));

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToHowToPlay, MainMenuState::goToAbout};
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

void MainMenuState::goToHowToPlay() {
    stateManager.changeState<HowToPlayMenuState>();
}

void MainMenuState::goToAbout() {
    stateManager.changeState<AboutMenuState>();
}
