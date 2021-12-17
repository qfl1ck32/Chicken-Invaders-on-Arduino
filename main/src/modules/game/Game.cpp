#include "./Game.h"

int8_t Game::maxLevel = 5;

Game::Game() {
    this->reset();
}

void Game::setSpaceship(int8_t x, int8_t y) {
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
    static int8_t spaceshipDefaultX = 7;
    static int8_t spaceshipDefaultY = 2;

    this->timeSinceLastStart = millis();

    if (this->needsInitialisation) {
        this->needsInitialisation = false;
        this->setSpaceship(spaceshipDefaultX, spaceshipDefaultY);
    }

    Chicken *chicken = new Chicken(0, random(Unit::engine->columns));

    chicken->eggDelayer.updateInterval(CHICKEN_INITIAL_EGG_DELAYER_INTERVAL / this->level);
    chicken->moveDelayer.updateInterval(CHICKEN_INITIAL_MOVE_DELAYER_INTERVAL / this->level);
}

void Game::changeLevel(int level) {
    if (level < 1 || level > Game::maxLevel) return;

    this->level = level;
}

void Game::goToNextLevel() {
    ++this->level;

    this->spaceship->lifes += 1;
}
