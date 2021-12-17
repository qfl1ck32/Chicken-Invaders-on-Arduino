#ifndef NameSelector_h
#define NameSelector_h

#include "../delayer/Delayer.h"
#include "../lcd/LCD.h"
#include "Arduino.h"

#define NAME_MAX_LENGTH 5

class NameSelector {
   public:
    LCD *lcd;

    short currentColumn;

    int row;

    bool isSelected = false;

    bool isInvalid = false;

    Delayer errorDelayer = Delayer(2000);

    char *name;

    short currentLetterIndex;

    NameSelector(LCD *lcd, int row) {
        this->lcd = lcd;
        this->row = row;

        this->name = new char[NAME_MAX_LENGTH];

        this->reset();
    }

    void goUp();
    void goRight();
    void goDown();
    void goLeft();

    void select();

    bool finish();

    void reset();

    void handleInvalidFinish();

    void main();
};

#endif
