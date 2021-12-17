#include "./LeaderboardState.h"

#include "../../globals.h"

void LeaderboardState::setup() {
    static const char noHighScoresMessage[] PROGMEM = "No high scores";

    static const uint64_t icon = 0xa5a5e52527243c00;

    HandlerFunction handlers[] = {LeaderboardState::goBack};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    leaderboard.generate();

    int numberOfHighscores = leaderboard.scores->size;

    char *messages[numberOfHighscores == 0 ? 2 : 1 + numberOfHighscores];

    char backMessageBuffer[5];

    readFromPROGMEM(backMessage, backMessageBuffer, 4);

    messages[0] = backMessageBuffer;

    int index = 1;

    while (leaderboard.scores->size) {
        NameAndScore entry = leaderboard.scores->removeHead();

        char leaderboardEntry[strlen(entry.name) + getNumberOfDigits(entry.score) + getNumberOfDigits(index) + 7];

        sprintf((char *)messages[index], "%d. %s - %d", index, entry.name, entry.score);

        free(entry.name);

        ++index;
    }

    if (index == 1) {
        char buffer[15];

        readFromPROGMEM(noHighScoresMessage, buffer, 14);

        messages[index] = buffer;
    }

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&icon);

    matrix->displayImage(image);
}

void LeaderboardState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void LeaderboardState::cleanup() {
    lcd->clear();

    joystick.clearHandlers();

    matrix->clear();
}

void LeaderboardState::goBack() {
    stateManager.changeState(mainMenuStateId);
    ;
}