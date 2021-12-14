#include "./PlayingState.h"

#include "../../globals.h"

void PlayingState::setup() {
    joystick.setOnChangeUp(PlayingState::moveUp);
    joystick.setOnChangeDown(PlayingState::moveDown);

    joystick.setOnChangeLeft(PlayingState::moveLeft);
    joystick.setOnChangeRight(PlayingState::moveRight);

    button.setOnStateChange(PlayingState::attack);

    if (game.needsInitialisation) {
        game.needsInitialisation = false;
        game.setSpaceship(7, 3);
    }

    new Chicken(0, game.level);
}

void PlayingState::handle() {
    joystick.handleJoystickMovements();
    gameEngine.run();

    gameStatus.show(game.score, game.spaceship->lifes, 0);
    graphicsEngine.renderChanges(gameEngine.changes, gameEngine.currentChangeIndex);
}

void PlayingState::cleanup() {
    lcd->clear();
    joystick.clearHandlers();
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
