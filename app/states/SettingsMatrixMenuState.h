#pragma once

class SettingsMatrixMenuState : public State {
   public:
    SettingsMatrixMenuState(int state) : State(state) {
    }

    void setup() {
        const char *messages[] = {"Go back", "Intensity +", "Intensity -"};

        menu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {SettingsMatrixMenuState::goBack, SettingsMatrixMenuState::increaseIntensity, SettingsMatrixMenuState::decreaseIntensity};

        menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

        joystick->setHandlerOnYAxisChangeUp(menuGoUp);
        joystick->setHandlerOnYAxisChangeDown(menuGoDown);

        joystick->setHandlerSwStateChange(menuSelect);

        for (int i = 0; i < matrix->rows; ++i) {
            for (int j = 0; j < matrix->columns; ++j) {
                matrix->setLed(0, i, j, true);
            }
        }
    }

    void handle() {
        menu->run();
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        joystick->clearHandlers();

        for (int i = 0; i < matrix->rows; ++i) {
            for (int j = 0; j < matrix->columns; ++j) {
                matrix->setLed(0, i, j, false);
            }
        }
    }

    static void goBack() {
        stateManager->changeState(settingsMenuStateId);
    }

    static void increaseIntensity() {
        matrix->increaseIntensity(2);
    }

    static void decreaseIntensity() {
        matrix->increaseIntensity(-2);
    }
};
