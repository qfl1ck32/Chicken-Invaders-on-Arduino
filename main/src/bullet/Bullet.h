#ifndef Bullet_h
#define Bullet_h

#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../unit/Unit.h"

class Bullet : public Unit {
   public:
    Bullet(int8_t, int8_t);

    // FIXME: if I put it in the constructor, the bullets are super-sonic
    Delayer delayer = Delayer(250);

    Bullet();

    void action();

    void behaviour(int8_t);

    unsigned char getType();
};

#endif
