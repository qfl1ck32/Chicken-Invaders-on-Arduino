#include "./PlayingState.h"

#include "../../globals.h"

void PlayingState::setup() {
    joystick.setOnChangeUp(PlayingState::moveUp);
    joystick.setOnChangeDown(PlayingState::moveDown);

    joystick.setOnChangeLeft(PlayingState::moveLeft);
    joystick.setOnChangeRight(PlayingState::moveRight);

    button.setOnStateChange(PlayingState::attack);

    game.setupLevel();

    lcd->shouldClearRowOnPrint = false;
}

void PlayingState::handle() {
    joystick.handleJoystickMovements();

    Unit::engine->run();

    gameStatus.show(game.score, game.spaceship->lifes, game.level, game.timeSinceLastStart);
    graphicsEngine.renderChanges(Unit::engine->pixelChanges);
}

void PlayingState::cleanup() {
    lcd->clear();
    joystick.clearHandlers();

    // TODO: should put it back how it was, not necessarily true
    lcd->shouldClearRowOnPrint = true;
}

void PlayingState::moveUp() {
    game.spaceship->move(-1, 0);
}

void PlayingState::moveRight() {
    game.spaceship->move(0, 1);
}

void PlayingState::moveDown() {
    game.spaceship->move(1, 0);
}

void PlayingState::moveLeft() {
    game.spaceship->move(0, -1);
}

void PlayingState::attack() {
    game.spaceship->attack();
}
