#ifndef GameStatus_h
#define GameStatus_h

#include "../../app/globals.h"
// #include "../../game-engine/GameEngine.h"
#include "../../lcd/LCD.h"
#include "../../utils/utils.h"

class GameStatus {
   public:
    LCD* lcd;

    GameStatus(LCD* lcd) {
        this->lcd = lcd;
    }

    void show(short score, short lifes, unsigned long startTime);
};

#endif
