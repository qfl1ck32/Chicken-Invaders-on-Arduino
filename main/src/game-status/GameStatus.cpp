#include "./GameStatus.h"

#include "../app/globals.h"

void GameStatus::displayHeader() {
    static const char msg[] PROGMEM = "Lvl Pts Time";

    char *firstRowString = readStringFromPROGMEM(msg);

    this->lcd->printOnRow(firstRowString, 0);

    this->lcd->setCursor(strlen(firstRowString) + 2, 0);
    this->lcd->write(heartChar);

    delete firstRowString;
}

void GameStatus::show(short score, int8_t lifes, int8_t level, int time) {
    char messageSecondRow[this->lcd->columns + 1];

    snprintf(messageSecondRow, this->lcd->columns, " %d %s%d  %s%d  %s%d", level, score > 10 ? " " : "  ", score, score < 100 ? " " : "", time, time >= 10 ? " " : "  ", lifes);

    messageSecondRow[this->lcd->columns] = '\0';

    this->lcd->printOnRow(messageSecondRow, 1);
}
