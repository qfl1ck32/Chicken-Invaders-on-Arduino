#ifndef Game_h
#define Game_h

#include "../../chicken/Chicken.h"
#include "../../spaceship/Spaceship.h"

class Chicken;
class Spaceship;

class Game {
   public:
    Spaceship *spaceship;
    short score;
    int8_t level;

    unsigned long timeSinceLastStart;

    static int8_t maxLevel;

    bool needsInitialisation;

    Game();

    void setSpaceship(int8_t, int8_t);

    void reset();

    void setupLevel();

    void changeLevel(int level);

    void goToNextLevel();
};

#endif
