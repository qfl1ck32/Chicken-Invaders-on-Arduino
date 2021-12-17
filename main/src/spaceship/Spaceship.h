#ifndef Spaceship_h
#define Spaceship_h

#include "../bullet/Bullet.h"
#include "../constants/app.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Spaceship : public Unit {
   public:
    short lifes;

    Spaceship(int8_t, int8_t);

    void action();
    void attack();

    void behaviour(int8_t);

    void move(short, short);

    unsigned char getType();
};

#endif
