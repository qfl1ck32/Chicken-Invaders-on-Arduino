#ifndef NameSelector_h
#define NameSelector_h

#include "../../delayer/Delayer.h"
#include "../../lcd/LCD.h"
#include "Arduino.h"

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

        this->name = new char[this->lcd->columns];

        for (int i = 0; i < this->lcd->columns; ++i) {
            this->name[i] = 0;
        }

        this->currentLetterIndex = 0;
        this->currentColumn = 0;
    }

    void goUp();
    void goRight();
    void goDown();
    void goLeft();

    void select();

    bool finish();

    void handleInvalidFinish();

    void main();
};

#endif
