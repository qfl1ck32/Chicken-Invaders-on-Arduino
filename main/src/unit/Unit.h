#ifndef Unit_h
#define Unit_h

#include "../game-engine/GameEngine.h"
#include "Arduino.h"

class GameEngine;

class Unit {
   public:
    static GameEngine *engine;

    virtual unsigned char getType() = 0;

    int8_t x, y, numberOfMessages;

    bool isAlive;

    int8_t *messages;

    Unit() {}

    virtual ~Unit() {
        delete[] this->messages;
    }

    Unit(int8_t, int8_t);

    void die();

    void move(short, short);

    bool isValidPosition(int8_t, int8_t);

    void sendMessage(int8_t, Unit &);

    virtual void action() = 0;
    virtual void behaviour(int8_t) = 0;

    void react();
};

#endif
