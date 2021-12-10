#pragma once

class SettingsMenuState : public State {
   public:
    SettingsMenuState(int state) : State(state) {
    }

    void setup() {
        const char *messages[] = {"Go back", "Contrast -", "Contrast +", "Backlight -", "Backlight +", "Matrix light +", "Matrix light -"};

        menu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {SettingsMenuState::goBack, SettingsMenuState::decreaseContrast, SettingsMenuState::increaseContrast,
                                      SettingsMenuState::decreaseBacklight, SettingsMenuState::increaseBacklight};

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

    static void increaseContrast() {
        lcd->changeContrast(-20);
    }

    static void decreaseContrast() {
        lcd->changeContrast(20);
    }

    static void increaseBacklight() {
        lcd->changeBacklight(10);
    }

    static void decreaseBacklight() {
        lcd->changeBacklight(-10);
    }
};
