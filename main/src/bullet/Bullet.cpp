#include "./Bullet.h"

#include "../app/globals.h"

Bullet::Bullet() {
    this->delayer.updateInterval(125);
}

Bullet::Bullet(int8_t x, int8_t y) : Unit(x, y) {
    static short frequency = 400;
    static int8_t duration = 125;

    songBuzzer->stop();

    gameSoundsBuzzer->buzz(frequency, duration);
}

void Bullet::action() {
    if (!this->delayer.canRun()) return;

    if (this->x == 0) {
        this->die();
        return;
    }

    if (this->engine->unitMatrix[this->x - 1][this->y] != 0 && this->engine->unitMatrix[this->x - 1][this->y]->getType() == CHICKEN_TYPE) {
        this->sendMessage(KILL, *this->engine->unitMatrix[this->x - 1][this->y]);
        this->die();
        return;
    }

    this->move(-1, 0);
};

void Bullet::behaviour(int8_t action){

};

unsigned char Bullet::getType() {
    return BULLET_TYPE;
}
