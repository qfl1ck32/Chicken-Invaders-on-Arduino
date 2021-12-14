#ifndef Unit_h
#define Unit_h

#include "../game-engine/GameEngine.h"
#include "Arduino.h"

class GameEngine;

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

#endif
