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
    byte level;

    static byte maxLevel;

    bool needsInitialisation;

    Game();

    void setSpaceship(byte, byte);

    void reset();

    void setupLevel();

    void changeLevel(int level);

    void goToNextLevel();
};

#endif
