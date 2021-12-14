#ifndef Game_h
#define Game_h

// #include "../../spaceship/Spaceship.h"

class Game {
   public:
    // Spaceship *spaceship;
    short score;
    short level;

    bool needsInitialisation;

    Game();

    void setSpaceship(short, short);

    void setChicken(short, short);

    void goToNextLevel();
};

#endif
