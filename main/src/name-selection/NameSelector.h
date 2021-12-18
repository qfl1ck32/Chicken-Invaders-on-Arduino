#ifndef NameSelector_h
#define NameSelector_h

#include "../lcd/LCD.h"

#define NAME_MAX_LENGTH 5

class NameSelector {
   public:
    LCD *lcd;

    short currentColumn;

    int row;

    bool isSelected = false;

    bool isInvalid = false;

    char *name;

    short currentLetterIndex;

    NameSelector(LCD *, int);
    ~NameSelector();

    void goUp();
    void goRight();
    void goDown();
    void goLeft();

    void select();

    bool finish();

    void main();
};

#endif
