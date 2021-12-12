#pragma once

#include "../game-engine/GameEngine.h"

#define MAX_MESSAGES 5

#define BULLET_TYPE 0
#define CHICKEN_TYPE 1
#define EGG_TYPE 2
#define SPACESHIP_TYPE 3

#define KILL 1

class Unit {
   public:
    static GameEngine *engine;

    virtual unsigned char getType() = 0;

    short x, y, numberOfMessages;

    bool isAlive;

    short *messages;

    Unit() {}

    virtual ~Unit() {
        delete[] this->messages;
    }

    Unit(short, short);

    void die();

    void move(short, short);

    bool isValidPosition(short, short);

    void sendMessage(short, Unit &);

    virtual void action() = 0;
    virtual void behaviour(short) = 0;

    void react();
};
