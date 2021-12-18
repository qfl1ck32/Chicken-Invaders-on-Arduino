#include "Unit.h"

#include "../app/globals.h"

GameEngine* Unit::engine = nullptr;

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
bool Unit::isValidPosition(int8_t x, int8_t y) {
    return Unit::engine->isValidPosition(x, y);
}

void Unit::move(short dx, short dy) {
    if (!this->isValidPosition(this->x + dx, this->y + dy)) {
        return;
    }

    Unit::engine->unitMatrix[this->x][this->y] = NULL;
    Unit::engine->pixelChanges->add(PixelChange(this->x, this->y, false));

    this->x += dx;
    this->y += dy;

    Unit::engine->unitMatrix[this->x][this->y] = this;
    Unit::engine->pixelChanges->add(PixelChange(this->x, this->y, true));
}

void Unit::sendMessage(int8_t message, Unit& unit) {
    if (unit.numberOfMessages != MAX_MESSAGES) {
        unit.messages[unit.numberOfMessages++] = message;
    }
}

Unit::Unit(int8_t x, int8_t y) {
    if (Unit::engine->unitMatrix[x][y] == NULL && Unit::engine->numberOfUnits < MAX_UNITS) {
        this->isAlive = true;

        this->x = x;
        this->y = y;

        this->numberOfMessages = 0;

        this->messages = new int8_t[MAX_MESSAGES];

        for (int i = 0; i < MAX_MESSAGES; ++i) {
            messages[i] = 0;
        }

        Unit::engine->unitArray[Unit::engine->numberOfUnits++] = this;
        Unit::engine->unitMatrix[x][y] = this;

        Unit::engine->pixelChanges->add(PixelChange(this->x, this->y, true));
    }

    // Dragulici!!!
    else {
        delete this;
    }
}
