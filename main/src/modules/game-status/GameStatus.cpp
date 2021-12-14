#include "./GameStatus.h"

#include "../../app/globals.h"

void GameStatus::show(short score, byte lifes, unsigned int startTime) {
    char scoreMessage[getNumberOfDigits(score) + 8];

    static const char* const scoreStr = "Score";

    sprintf(scoreMessage, "%s: %d", scoreStr, score);

    this->lcd->printOnRow(scoreMessage, 0);

    char lifesMessage[getNumberOfDigits(lifes) + 1];

    sprintf(lifesMessage, "%d", lifes);

    // this->lcd->printOnRow("|", 0, strlen(scoreMessage) + 3);

    this->lcd->printOnRow(lifesMessage, 1);

    // this->lcd->printOnRowAndColumn(heartChar, 1, strlen(lifesMessage) + 1, true);
}
