#ifndef Spaceship_h
#define Spaceship_h

#include "../app/states/GameOverState/GameOverState.h"
#include "../bullet/Bullet.h"
#include "../constants/app.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class GameOverState;

class Spaceship : public Unit {
   public:
    short lifes;

    Spaceship(int8_t x, int8_t y) : Unit(x, y) {
        this->lifes = 3;
    }

    void action();
    void attack();

    void behaviour(int8_t);

    void move(short, short);

    unsigned char getType();
};

#endif
