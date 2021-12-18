#ifndef GameStatus_h
#define GameStatus_h

#include "../lcd/LCD.h"
#include "../utils/utils.h"

class GameStatus {
   public:
    LCD* lcd;

    GameStatus(LCD* lcd) {
        this->lcd = lcd;
    }

    void displayHeader();
    void show(short, int8_t, int8_t, int);
};

#endif
