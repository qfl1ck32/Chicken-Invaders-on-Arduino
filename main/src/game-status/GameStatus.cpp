#include "./GameStatus.h"

#include "../app/globals.h"

void GameStatus::displayHeader() {
    static const char msg[] PROGMEM = "Lvl Pts Secs Lfs";

    char *firstRowString = readStringFromPROGMEM(msg);

    this->lcd->printOnRow(firstRowString, 0);

    delete firstRowString;
}

void GameStatus::show(short score, int8_t lifes, int8_t level, int time) {
    char *messageSecondRow = new char[this->lcd->columns + 1];

    sprintf(messageSecondRow, " %d   %d   %d   %d", level, score, time, lifes);

    messageSecondRow[this->lcd->columns] = '\0';

    this->lcd->printOnRow(messageSecondRow, 1);

    delete messageSecondRow;
}
