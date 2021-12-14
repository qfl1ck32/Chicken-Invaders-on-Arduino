#include "./LeaderboardState.h"

#include "../../globals.h"

void LeaderboardState::setup() {
    HandlerFunction handlers[] = {LeaderboardState::goBack};

    menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    LinkedList<NameAndScore> *scores = leaderboard->get();

    int numberOfHighscores = scores->size();

    const char *messages[numberOfHighscores == 0 ? 2 : 1 + numberOfHighscores];

    static const char *const back PROGMEM = "Back";

    messages[0] = back;

    int index = 1;

    while (scores->size()) {
        NameAndScore entry = scores->remove(0);

        // char leaderboardEntry[strlen(entry.name) + getNumberOfDigits(entry.score) + getNumberOfDigits(index) + 7];

        // sprintf(messages[index], "%d. %s - %d", index, entry.name, entry.score);

        // TODO: come back and format w/ score too
        messages[index] = entry.name;

        // TODO: feels stupid
        // free(entry.name);

        // show("Bag fix asta:::", entry.name);

        ++index;
    }

    if (index == 1) {
        messages[index] = "No high scores";
    }

    free(scores);

    menu->setMessages(messages, sizeof(messages) / sizeof(char *));

    joystick->setHandlerOnYAxisChangeUp(menuGoUp);
    joystick->setHandlerOnYAxisChangeDown(menuGoDown);

    joystick->setHandlerSwStateChange(menuSelect);
}

void LeaderboardState::handle() {
    menu->run();
    joystick->handleJoystickMovements();
}

void LeaderboardState::cleanup() {
    lcd->clear();

    joystick->clearHandlers();
}

void LeaderboardState::goBack() {
    stateManager->changeState<MainMenuState>();
}