#include "./Game.h"

Game::Game() {
    this->spaceship = 0;
    this->score = 0;

    this->level = 1;

    this->needsInitialisation = true;
}

void Game::setSpaceship(short x, short y) {
    if (this->spaceship == 0) {
        this->spaceship = new Spaceship(x, y);
    }
}

void Game::setChicken(short x, short y) {
    new Chicken(x, y);
}

void Game::goToNextLevel() {
    ++this->level;
}