#pragma once

#include <LinkedList.h>

#include "../app/app.h"
#include "../pixel-change/PixelChange.h"

#define MAX_SPACESHIP_SHOTS 10

#define MAX_UNITS 15

class Unit;

class GameEngine {
   public:
    Unit *unitMatrix[9][9];
    Unit *unitArray[MAX_UNITS];

    Matrix *matrix;

    LinkedList<PixelChange> *changes;

    int numberOfUnits;

    // FIXME: should be somewhere else...
    int score;

    int finalScore;

    GameEngine(Matrix *&);

    void resetState();

    void handleDisplay();

    void run();

    bool isValidPosition(short, short);
};
