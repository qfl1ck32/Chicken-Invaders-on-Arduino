#include "./Game.h"

byte Game::maxLevel = 5;

Game::Game() {
    this->reset();
}

void Game::setSpaceship(byte x, byte y) {
    if (this->spaceship == 0) {
        this->spaceship = new Spaceship(x, y);
    }
}

void Game::reset() {
    this->score = 0;
    this->level = 1;
    this->spaceship = 0;
    this->needsInitialisation = true;
}

void Game::setupLevel() {
    // FIXME coordinates for spaceship?
    if (this->needsInitialisation) {
        this->needsInitialisation = false;
        this->setSpaceship(6, 2);
    }

    switch (this->level) {
        case 1:
            new Chicken(0, random(Unit::engine->columns));
            break;

        case 2:
            new Chicken(0, random(Unit::engine->columns));
            new Chicken(1, random(Unit::engine->columns));
            break;

        default:
            new Chicken(0, random(Unit::engine->columns / 2));
            new Chicken(0, random(Unit::engine->columns / 2, Unit::engine->columns));

            new Chicken(1, random(Unit::engine->columns / 2));
            new Chicken(1, random(Unit::engine->columns / 2, Unit::engine->columns));
            return;
    }
}

void Game::changeLevel(int level) {
    if (this->level < 1 || this->level > Game::maxLevel) return;

    this->level = level;
}

void Game::goToNextLevel() {
    ++this->level;

    // FIXME: you earn a life when you win. move the logic?
    this->spaceship->lifes += 1;
}