#include "./PlayingState.h"

#include "../../globals.h"

int8_t PlayingState::maxLevel = 5;

Spaceship* PlayingState::spaceship = 0;

PlayingState::PlayingState() {
    this->graphicsEngine = new GraphicsEngine(matrix);
    this->gameStatus = new GameStatus(lcd);
}

PlayingState::~PlayingState() {
    delete this->graphicsEngine;
    delete this->gameStatus;
}

void PlayingState::setup() {
    joystick.setOnChangeUp(PlayingState::moveUp);
    joystick.setOnChangeDown(PlayingState::moveDown);

    joystick.setOnChangeLeft(PlayingState::moveLeft);
    joystick.setOnChangeRight(PlayingState::moveRight);

    button.setOnStateChange(PlayingState::attack);

    this->setupLevel();

    lcd->shouldClearRowOnPrint = false;
}

void PlayingState::handle() {
    joystick.handleJoystickMovements();

    Unit::engine->run();

    this->gameStatus->show(this->score, PlayingState::spaceship->lifes, level, this->timeSinceLastStart);
    this->graphicsEngine->renderChanges(Unit::engine->pixelChanges);
}

void PlayingState::setSpaceship(int8_t x, int8_t y) {
    if (PlayingState::spaceship == 0) {
        PlayingState::spaceship = new Spaceship(x, y);
    }
}

void PlayingState::reset() {
    this->score = 0;
    PlayingState::spaceship = 0;
    this->needsInitialisation = true;
}

void PlayingState::setupLevel() {
    static int8_t spaceshipDefaultX = 7;
    static int8_t spaceshipDefaultY = 2;

    this->timeSinceLastStart = millis();

    if (this->needsInitialisation) {
        this->needsInitialisation = false;
        this->setSpaceship(spaceshipDefaultX, spaceshipDefaultY);
    }

    Chicken* chicken = new Chicken(0, random(Unit::engine->columns));

    chicken->eggDelayer.updateInterval(CHICKEN_INITIAL_EGG_DELAYER_INTERVAL / level);
    chicken->moveDelayer.updateInterval(CHICKEN_INITIAL_MOVE_DELAYER_INTERVAL / level);
}

void PlayingState::cleanup() {
    lcd->clear();
    matrix->setAllLeds(false);

    joystick.clearHandlers();

    // TODO: should put it back how it was, not necessarily true
    lcd->shouldClearRowOnPrint = true;
}

void PlayingState::moveUp() {
    PlayingState::spaceship->move(-1, 0);
}

void PlayingState::moveRight() {
    PlayingState::spaceship->move(0, 1);
}

void PlayingState::moveDown() {
    PlayingState::spaceship->move(1, 0);
}

void PlayingState::moveLeft() {
    PlayingState::spaceship->move(0, -1);
}

void PlayingState::attack() {
    PlayingState::spaceship->attack();
}
