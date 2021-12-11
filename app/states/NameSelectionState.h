#pragma once

class NameSelectionState : public State {
   public:
    NameSelectionState(int state) : State(state) {}

    void handle() {
        joystick->handleJoystickMovementOnAxisX();
        joystick->handleJoystickMovementOnAxisY();

        nameSelector->main();
    }

    void setup() {
        joystick->setHandlerOnXAxisChangeLeft(NameSelectionState::goLeft);
        joystick->setHandlerOnXAxisChangeRight(NameSelectionState::goRight);
        joystick->setHandlerOnYAxisChangeUp(NameSelectionState::goUp);
        joystick->setHandlerOnYAxisChangeDown(NameSelectionState::goDown);
        joystick->setHandlerSwStateChange(NameSelectionState::handleSwStateChange);

        button->setOnStateChange(NameSelectionState::finish);
    }

    void cleanup() {
        joystick->clearHandlers();

        button->clearHandler();

        lcd->clear();
        lcd->noBlink();
    }

    static void goUp() {
        nameSelector->goUp();
    }

    static void goDown() {
        nameSelector->goDown();
    }

    static void goLeft() {
        nameSelector->goLeft();
    }

    static void goRight() {
        nameSelector->goRight();
    }

    static void handleSwStateChange() {
        nameSelector->select();
    }

    static void finish() {
        if (nameSelector->finish()) {
            // TODO: update logic
            leaderboard->write(nameSelector->name, gameEngine->score);
            stateManager->changeState(mainMenuStateId);
        }
    }
};
