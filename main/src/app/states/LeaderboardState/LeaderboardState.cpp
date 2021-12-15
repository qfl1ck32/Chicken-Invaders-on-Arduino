#include "./LeaderboardState.h"

#include "../../globals.h"

void LeaderboardState::setup() {
    HandlerFunction handlers[] = {LeaderboardState::goBack};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    NameAndScore *scores = leaderboard.get();

    // FIXME keep in mind, max n scores, display "Missing" for the rest if needed

    // int numberOfHighscores = scores->size();

    // const char *messages[numberOfHighscores == 0 ? 2 : 1 + numberOfHighscores];

    // static const char *const back = "Back";

    // messages[0] = back;

    // int index = 1;

    // while (scores->size()) {
    //     NameAndScore entry = scores->remove(0);

    //     // char leaderboardEntry[strlen(entry.name) + getNumberOfDigits(entry.score) + getNumberOfDigits(index) + 7];

    //     // sprintf(messages[index], "%d. %s - %d", index, entry.name, entry.score);

    //     // TODO: come back and format w/ score too
    //     messages[index] = entry.name;

    //     // TODO: feels stupid
    //     // free(entry.name);

    //     // show("Bag fix asta:::", entry.name);

    //     ++index;
    // }

    // if (index == 1) {
    //     messages[index] = "No high scores";
    // }

    // free(scores);

    // menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    // joystick.setOnChangeUp(menuGoUp);
    // joystick.setOnChangeDown(menuGoDown);

    // joystick.setOnSwStateChange(menuSelect);
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