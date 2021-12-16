#include "./GameStatus.h"

#include "../../app/globals.h"

void GameStatus::show(short score, byte lifes, byte level, unsigned int startTime) {
    // TODO: progmem :)

    char messageFirstRow[this->lcd->columns];
    char messageSecondRow[this->lcd->columns];

    sprintf(messageFirstRow, "Lvl Pts Secs Lfs");
    sprintf(messageSecondRow, " %d   %d   %d   %d", level, score, (int)(millis() - startTime) / 1000, lifes);

    this->lcd->printOnRow(messageFirstRow, 0);
    this->lcd->printOnRow(messageSecondRow, 1);
}
