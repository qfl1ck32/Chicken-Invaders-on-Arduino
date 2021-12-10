#pragma once

class MainMenuState : public State {
   public:
    MainMenuState(int state) : State(state) {
    }

    void setup() {
        const char *messages[] = {"Play", "Settings", "Leaderboard", "About"};

        menu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToAbout};
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
        button->clearHandler();

        lcd->clear();
    }

    static void goToPlay() {
        stateManager->changeState(playingStateId);
    }

    static void goToSettings() {
        stateManager->changeState(settingsMenuStateId);
    }

    static void goToLeaderboard() {
        stateManager->changeState(leaderboardMenuStateId);
    }

    static void goToAbout() {
        stateManager->changeState(aboutMenuStateId);
    }
};
