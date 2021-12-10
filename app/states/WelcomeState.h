#pragma once

class WelcomeState : public State {
   public:
    WelcomeState(int state) : State(state) {}

    void setup() {
        button->setOnStateChange(WelcomeState::moveToEnterYourNameState);
    }

    void handle() {
        greeter->run();
    }

    void cleanup() {
        button->clearHandler();
        lcd->clear();
    }

    static void moveToEnterYourNameState() {
        stateManager->changeState(mainMenuStateId);
    }
};
