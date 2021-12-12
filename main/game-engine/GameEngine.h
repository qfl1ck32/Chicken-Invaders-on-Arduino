#pragma once

#include <LinkedList.h>

#include "../app/globals.h"
#include "../pixel-change/PixelChange.h"

#define MAX_UNITS 10

class Unit;

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
