#pragma once

#include "../../chicken/Chicken.h"
#include "../../spaceship/Spaceship.h"
#include "../app.h"

class PlayingState : public State {
   public:
    short level;
    unsigned long startTime;

    PlayingState(int state) : State(state) {
        this->level = 1;
    }

    void setup() {
        this->startTime = millis();

        gameEngine->resetState();

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

    void handle() {
        joystick->handleJoystickMovements();
        gameEngine->run();
        gameStatus->show(gameEngine->score, spaceship->lifes, this->startTime);
        graphicsEngine->renderChanges(gameEngine->changes);
    }

    void cleanup() {
        lcd->clear();
        joystick->clearHandlers();
    }

    void setLevel(short);

    static void moveUp() {
        spaceship->move(-1, 0);
    }

    static void moveRight() {
        spaceship->move(0, 1);
    }

    static void moveDown() {
        spaceship->move(1, 0);
    }

    static void moveLeft() {
        spaceship->move(0, -1);
    }

    static void attack() {
        spaceship->attack();
    }
};

void PlayingState::setLevel(short level) {
    this->level = level;
}