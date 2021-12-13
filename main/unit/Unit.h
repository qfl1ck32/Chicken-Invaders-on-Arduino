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

    byte x, y, numberOfMessages;

    bool isAlive;

    byte *messages;

    Unit() {}

    virtual ~Unit() {
        delete[] this->messages;
    }

    Unit(byte, byte);

    void die();

    void move(byte, byte);

    bool isValidPosition(byte, byte);

    void sendMessage(byte, Unit &);

    virtual void action() = 0;
    virtual void behaviour(byte) = 0;

    void react();
};
