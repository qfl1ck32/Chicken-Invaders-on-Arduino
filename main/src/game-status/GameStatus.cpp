#include "./GameStatus.h"

#include "../app/globals.h"

void GameStatus::show(short score, int8_t lifes, int8_t level, int time) {
    const char msg[] PROGMEM = "Lvl Pts Secs Lfs";

    char messageSecondRow[this->lcd->columns];

    sprintf(messageSecondRow, " %d   %d   %d   %d", level, score, time, lifes);

    char *firstRowString = readStringFromPROGMEM(msg);

    this->lcd->printOnRow(firstRowString, 0);
    this->lcd->printOnRow(messageSecondRow, 1);

    delete firstRowString;
}
