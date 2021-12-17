#include "./LeaderboardState.h"

#include "../../globals.h"

LeaderboardState::LeaderboardState() {
    this->leaderboard = new Leaderboard();
}

LeaderboardState::~LeaderboardState() {
    delete this->leaderboard;
}

void LeaderboardState::setup() {
    // TODO: progmem
    static const char noHighScoresMessage[] PROGMEM = "No high scores";

    static const uint64_t icon PROGMEM = 0xa5a5e52527243c00;

    HandlerFunction handlers[] = {LeaderboardState::goBack};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    this->leaderboard->generate();

    int numberOfHighscores = this->leaderboard->scores->size;

    while (this->leaderboard->scores->size) {
        NameAndScore str = this->leaderboard->scores->removeHead();

        Serial.println(str.name);
        Serial.println(str.score);
        Serial.println("<<<");
    }

    // char *messages[numberOfHighscores == 0 ? 2 : 1 + numberOfHighscores];

    // // TODO: backMessage
    // const char *goBak = "Go back";

    // messages[0] = (char *)goBak;

    // int index = 1;

    // while (leaderboard->scores->size) {
    //     NameAndScore entry = leaderboard->scores->removeHead();

    //     char leaderboardEntry[strlen(entry.name) + getNumberOfDigits(entry.score) + getNumberOfDigits(index) + 7];

    //     sprintf((char *)messages[index], "%d. %s - %d", index, entry.name, entry.score);

    //     free(entry.name);

    //     ++index;
    // }

    // // TODO: progmem
    // if (index == 1) {
    //     messages[index] = (char *)noHighScoresMessage;
    // }

    static const char *const messages[] PROGMEM = {backMessage, noHighScoresMessage};

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

    matrix->setAllLeds(false);
}

void LeaderboardState::goBack() {
    stateManager.changeState<MainMenuState>();
}
