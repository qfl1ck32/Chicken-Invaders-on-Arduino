#ifndef GameEngine_h
#define GameEngine_h

#include <LinkedList.h>

#include "../pixel-change/PixelChange.h"
#include "../unit/Unit.h"

#define MAX_UNITS 10

class Unit;

class PixelChange;

class GameEngine {
   public:
    short rows, columns;

    Unit ***unitMatrix;
    Unit *unitArray[MAX_UNITS];

    LinkedList<PixelChange> *changes;

    int numberOfUnits;

    GameEngine(short, short);

    void resetState();

    void handleDisplay();

    void run();

    bool isValidPosition(short, short);
};

#endif
