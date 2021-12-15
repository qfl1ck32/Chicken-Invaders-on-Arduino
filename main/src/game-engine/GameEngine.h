#ifndef GameEngine_h
#define GameEngine_h

#include "../constants/app.h"
#include "../pixel-change/PixelChange.h"
#include "../unit/Unit.h"
#include "Arduino.h"

#define MAX_UNITS 10
#define MAX_CHANGES 10

class Unit;

class PixelChange;

class GameEngine {
   public:
    byte rows, columns;

    Unit *unitMatrix[MATRIX_ROWS][MATRIX_COLUMNS];
    Unit *unitArray[MAX_UNITS];

    byte currentChangeIndex;

    PixelChange changes[MAX_CHANGES];

    byte numberOfUnits;

    GameEngine(byte, byte);

    void resetState();

    void handleDisplay();

    void run();

    bool isValidPosition(byte, byte);

    void resetChanges();
};

#endif
