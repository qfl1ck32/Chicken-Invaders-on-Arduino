#ifndef Bullet_h
#define Bullet_h

#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Bullet : public Unit {
   public:
    Bullet(int8_t, int8_t);

    Delayer delayer;

    Bullet();

    void action();

    void behaviour(int8_t);

    unsigned char getType();
};

#endif
