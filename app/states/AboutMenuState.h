#pragma once

class AboutMenuState : public State {
   public:
    AboutMenuState(int state) : State(state) {
    }

    void setup() {
        const char *messages[] = {"Back", "App Name: Chicken Invaders", "Programmer: Rusu Andrei-Cristian",
                                  "Github: https://github.com/qfl1ck32/Chicken-Invaders-on-Arduino"};

        menu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {AboutMenuState::goBack};
        menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

        joystick->clearHandlers();
        button->clearHandler();

        joystick->setHandlerOnYAxisChangeUp(menuGoUp);
        joystick->setHandlerOnYAxisChangeDown(menuGoDown);

        joystick->setHandlerSwStateChange(menuSelect);
    }

    void handle() {
        menu->run(true);
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        joystick->clearHandlers();
        button->clearHandler();

        lcd->clear();
    }

    static void goBack() {
        stateManager->changeState(mainMenuStateId);
    }
};
