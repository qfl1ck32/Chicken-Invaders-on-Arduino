#pragma once

class SettingsMenuState : public State {
   public:
    SettingsMenuState(int state) : State(state) {
    }

    void setup() {
        const char *messages[] = {"Go back", "Level", "LCD", "Matrix"};

        menu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {SettingsMenuState::goBack, SettingsMenuState::goToLevel, SettingsMenuState::goToLCD,
                                      SettingsMenuState::goToMatrix};

        menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

        joystick->setHandlerOnYAxisChangeUp(menuGoUp);
        joystick->setHandlerOnYAxisChangeDown(menuGoDown);

        joystick->setHandlerSwStateChange(menuSelect);
    }

    void handle() {
        menu->run();
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        joystick->clearHandlers();
    }

    static void goBack() {
        stateManager->changeState(mainMenuStateId);
    }

    static void goToLevel() {
        // TODO
    }

    static void goToLCD() {
        stateManager->changeState(settingsLCDMenuStateId);
    }

    static void goToMatrix() {
        stateManager->changeState(settingsMatrixMenuStateId);
    }
};
