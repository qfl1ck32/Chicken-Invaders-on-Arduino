#include "./LeaderboardState.h"

#include "../../globals.h"

void LeaderboardState::setup() {
    HandlerFunction handlers[] = {LeaderboardState::goBack};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    leaderboard.generate();

    int numberOfHighscores = leaderboard.scores->size;

    const char *messages[numberOfHighscores == 0 ? 2 : 1 + numberOfHighscores];

    static const char *const back = "Back";

    messages[0] = back;

    int index = 1;

    while (leaderboard.scores->size) {
        NameAndScore entry = leaderboard.scores->removeHead();

        char leaderboardEntry[strlen(entry.name) + getNumberOfDigits(entry.score) + getNumberOfDigits(index) + 7];

        sprintf((char *)messages[index], "%d. %s - %d", index, entry.name, entry.score);

        free(entry.name);

        ++index;
    }

    if (index == 1) {
        messages[index] = "No high scores";
    }

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void LeaderboardState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void LeaderboardState::cleanup() {
    lcd->clear();

    joystick.clearHandlers();
}

void LeaderboardState::goBack() {
    stateManager.changeState(mainMenuStateId);
    ;
}