#include "Unit.h"

#include "../game-engine/GameEngine.cpp"
#include "../game-engine/GameEngine.h"

GameEngine* Unit::engine = gameEngine;

void Unit::die() {
    this->isAlive = false;
}

void Unit::react() {
    for (int i = 0; i < this->numberOfMessages; ++i) {
        if (this->messages[i] && this->isAlive) {
            this->behaviour(this->messages[i]);
        }
    }

    this->numberOfMessages = 0;
}

// TODO: this is overridable (just a notice, not a todo, lol)
bool Unit::isValidPosition(short x, short y) {
    return Unit::engine->isValidPosition(x, y);
}

void Unit::move(short dx, short dy) {
    if (!this->isValidPosition(this->x + dx, this->y + dy)) {
        return;
    }

    Unit::engine->unitMatrix[this->x][this->y] = NULL;
    Unit::engine->changes->add(PixelChange(this->x, this->y, false));

    this->x += dx;
    this->y += dy;

    Unit::engine->unitMatrix[this->x][this->y] = this;
    Unit::engine->changes->add(PixelChange(this->x, this->y, true));
}

void Unit::sendMessage(short message, Unit& unit) {
    if (unit.numberOfMessages != MAX_MESSAGES) {
        unit.messages[unit.numberOfMessages++] = message;
    }
}

Unit::Unit(short x, short y) {
    isAlive = true;

    this->x = x;
    this->y = y;

    this->numberOfMessages = 0;

    this->messages = new short[MAX_MESSAGES];

    // TODO: needs init.?
    for (int i = 0; i < MAX_MESSAGES; ++i) {
        messages[i] = 0;
    }

    // TODO: remove hardcoded 5
    // if (Unit::engine.unitMatrix[x][y] == NULL && Unit::engine.numberOfUnits < 5) {
    if (true) {
        Unit::engine->unitArray[Unit::engine->numberOfUnits++] = this;
        Unit::engine->unitMatrix[x][y] = this;
    }

    Unit::engine->changes->add(PixelChange(this->x, this->y, true));
}
