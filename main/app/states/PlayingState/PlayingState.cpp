#pragma once

#include "./PlayingState.h"

#include "../../../modules/game/Game.cpp"
#include "../../globals.h"

Game* PlayingState::game = new Game();

void PlayingState::setup() {
    joystick->setHandlerOnYAxisChangeUp(PlayingState::moveUp);
    joystick->setHandlerOnYAxisChangeDown(PlayingState::moveDown);

    joystick->setHandlerOnXAxisChangeLeft(PlayingState::moveLeft);
    joystick->setHandlerOnXAxisChangeRight(PlayingState::moveRight);

    button->setOnStateChange(PlayingState::attack);

    if (PlayingState::game->needsInitialisation) {
        PlayingState::game->needsInitialisation = false;

        this->game->setSpaceship(7, 3);
    }

    new Chicken(0, PlayingState::game->level);
}

void PlayingState::handle() {
    joystick->handleJoystickMovements();
    gameEngine->run();

    // TODO: add startTime
    gameStatus->show(this->game->score, this->game->spaceship->lifes, 0);
    graphicsEngine->renderChanges(gameEngine->changes);
}

void PlayingState::cleanup() {
    lcd->clear();
    joystick->clearHandlers();
}

void PlayingState::moveUp() {
    PlayingState::game->spaceship->move(-1, 0);
}

void PlayingState::moveRight() {
    PlayingState::game->spaceship->move(0, 1);
}

void PlayingState::moveDown() {
    PlayingState::game->spaceship->move(1, 0);
}

void PlayingState::moveLeft() {
    PlayingState::game->spaceship->move(0, -1);
}

void PlayingState::attack() {
    PlayingState::game->spaceship->attack();
}
