#ifndef GameEngine_h
#define GameEngine_h

#include "../constants/app.h"
#include "../linked-list/LinkedList.h"
#include "../pixel-change/PixelChange.h"
#include "../unit/Unit.h"
#include "Arduino.h"

#define MAX_UNITS 6

class Unit;

class PixelChange;

class GameEngine {
   public:
    byte rows, columns;

    Unit ***unitMatrix;
    Unit *unitArray[MAX_UNITS];

    LinkedList<PixelChange> *pixelChanges;

    byte numberOfUnits;

    GameEngine(byte, byte);

    void resetState();

    void handleDisplay();

    void run();

    bool isValidPosition(byte, byte);
};

#endif
