#pragma once

class AboutMenuState : public State {
   public:
    AboutMenuState(int state) : State(state) {
        const char *messages[] = {"Back", "-Chicken Invaders-.", "Programmer: Rusu", "Designer: Rusu", "NoSleeper: Rusu"};

        aboutMenu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {AboutMenuState::goBack};
        aboutMenu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));
    }

    void setup() {
        joystick->clearHandlers();
        button->clearHandler();

        joystick->setHandlerOnYAxisChangeUp(goUp);
        joystick->setHandlerOnYAxisChangeDown(goDown);

        joystick->setHandlerSwStateChange(AboutMenuState::select);
    }

    void handle() {
        aboutMenu->run(true);
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        joystick->clearHandlers();
        button->clearHandler();

        lcd->clear();
    }

    static void goUp() {
        aboutMenu->goUp();
    }

    static void goDown() {
        aboutMenu->goDown();
    }

    static void select() {
        aboutMenu->select();
    }

    static void goBack() {
        stateManager->changeState(mainMenuStateId);
    }
};
