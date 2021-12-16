#ifndef GameStatus_h
#define GameStatus_h

#include "../../lcd/LCD.h"
#include "../../utils/utils.h"

class GameStatus {
   public:
    LCD* lcd;

    GameStatus(LCD* lcd) {
        this->lcd = lcd;
    }

    void show(short, byte, byte, unsigned int);
};

#endif
