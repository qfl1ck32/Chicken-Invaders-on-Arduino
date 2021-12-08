#pragma once

class SettingsMenuState : public State {
   public:
    SettingsMenuState(int state) : State(state) {
        const char *messages[] = {"Go back", "Contrast -", "Contrast +", "Backlight -", "Backlight +"};

        settingsMenu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {SettingsMenuState::goBack, SettingsMenuState::decreaseContrast, SettingsMenuState::increaseContrast,
                                      SettingsMenuState::decreaseBacklight, SettingsMenuState::increaseBacklight};

        settingsMenu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));
    }

    void setup() {
        joystick->setHandlerOnYAxisChangeUp(SettingsMenuState::goUp);
        joystick->setHandlerOnYAxisChangeDown(SettingsMenuState::goDown);

        joystick->setHandlerSwStateChange(SettingsMenuState::select);
    }

    void handle() {
        settingsMenu->run();
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        joystick->clearHandlers();
    }

    static void goUp() {
        settingsMenu->goUp();
    }

    static void goDown() {
        settingsMenu->goDown();
    }

    static void select() {
        settingsMenu->select();
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
