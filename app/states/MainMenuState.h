#pragma once

class MainMenuState : public State {
   public:
    MainMenuState(int state) : State(state) {
        const char *messages[] = {"Play", "Settings", "Leaderboard", "About"};

        mainMenu->setMessages(messages, sizeof(messages) / sizeof(char *));

        HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToAbout};
        mainMenu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));
    }

    void setup() {
        joystick->setHandlerOnYAxisChangeUp(MainMenuState::goUp);
        joystick->setHandlerOnYAxisChangeDown(MainMenuState::goDown);

        joystick->setHandlerSwStateChange(MainMenuState::select);
    }

    void handle() {
        mainMenu->run();
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        joystick->clearHandlers();
        button->clearHandler();

        lcd->clear();
    }

    static void goUp() {
        mainMenu->goUp();
    }

    static void goDown() {
        mainMenu->goDown();
    }

    static void select() {
        mainMenu->select();
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
