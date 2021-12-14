#include "./Game.h"

Game::Game() {
    this->spaceship = 0;
    this->score = 0;

    this->level = 1;

    this->needsInitialisation = true;
}

void Game::setSpaceship(byte x, byte y) {
    if (this->spaceship == 0) {
        this->spaceship = new Spaceship(x, y);
    }
}

void Game::goToNextLevel() {
    ++this->level;
}