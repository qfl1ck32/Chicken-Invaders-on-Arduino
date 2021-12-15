#include "./Bullet.h"

#include "../app/globals.h"

Bullet::Bullet(byte x, byte y) : Unit(x, y) {
    static short frequency = 400;
    static byte duration = 125;

    // TODO: maybe move this logic somewhere?
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

void Bullet::behaviour(byte action){

};

unsigned char Bullet::getType() {
    return BULLET_TYPE;
}
