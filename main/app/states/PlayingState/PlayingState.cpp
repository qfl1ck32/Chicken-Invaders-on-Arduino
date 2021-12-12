#pragma once

#include "./PlayingState.h"

#include "../../../chicken/Chicken.cpp"
#include "../../../spaceship/Spaceship.cpp"
#include "../../globals.h"

Spaceship *spaceship = 0;

void PlayingState::setup() {
    joystick->setHandlerOnYAxisChangeUp(PlayingState::moveUp);
    joystick->setHandlerOnYAxisChangeDown(PlayingState::moveDown);

    joystick->setHandlerOnXAxisChangeLeft(PlayingState::moveLeft);
    joystick->setHandlerOnXAxisChangeRight(PlayingState::moveRight);

    button->setOnStateChange(PlayingState::attack);

    if (spaceship != 0) {
        delete spaceship;
    }

    spaceship = new Spaceship(7, 3);

    new Chicken(0, 3);

    new Chicken(0, 5);

    // TODO: create a nice handler for the level
    // switch (this->level) {
    //     case 1:
    //         new Chicken(0, 3);
    //         break;
    //     case 2:
    //         new Chicken(0, 3);
    //         new Chicken(0, 5);
    //         break;
    // }
}

void PlayingState::handle() {
    joystick->handleJoystickMovements();
    gameEngine->run();

    // TODO: add startTime
    gameStatus->show(gameEngine->score, spaceship->lifes, 0);
    graphicsEngine->renderChanges(gameEngine->changes);
}

void PlayingState::cleanup() {
    lcd->clear();
    joystick->clearHandlers();
}

void PlayingState::moveUp() {
    spaceship->move(-1, 0);
}

void PlayingState::moveRight() {
    spaceship->move(0, 1);
}

void PlayingState::moveDown() {
    spaceship->move(1, 0);
}

void PlayingState::moveLeft() {
    spaceship->move(0, -1);
}

void PlayingState::attack() {
    spaceship->attack();
}
