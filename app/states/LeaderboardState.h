#pragma once

class LeaderboardState : public State {
   public:
    LeaderboardState(int state) : State(state) {
        HandlerFunction handlers[] = {LeaderboardState::goBack};

        leaderboardMenu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

        // LinkedList<String> *scores = leaderboard->get();

        // int numberOfHighscores = scores->size();

        int numberOfHighscores = 0;

        // String messages[numberOfHighscores == 0 ? 2 : numberOfHighscores];

        const char *messages[] = {"Go back", "No haiscors"};

        // messages[0] = "Go back";

        int index = 1;

        // while (scores->size()) {
        //     String entry = scores->get(0);

        //     scores->remove(0);

        //     messages[index] = String(index);

        //     messages[index].concat(". ");
        //     messages[index].concat(entry);

        //     ++index;
        // }

        if (index == 1) {
            messages[index] = "No high scores";
        }

        // free(scores);

        leaderboardMenu->setMessages(messages, sizeof(messages) / sizeof(char *));
    }

    void setup() {
        joystick->setHandlerOnYAxisChangeUp(LeaderboardState::goUp);
        joystick->setHandlerOnYAxisChangeDown(LeaderboardState::goDown);

        joystick->setHandlerSwStateChange(LeaderboardState::select);
    }

    void handle() {
        leaderboardMenu->run();
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        lcd->clear();

        joystick->clearHandlers();
    }

    static void goUp() {
        leaderboardMenu->goUp();
    }

    static void goDown() {
        leaderboardMenu->goDown();
    }

    static void select() {
        leaderboardMenu->select();
    }

    static void goBack() {
        stateManager->changeState(mainMenuStateId);
    }
};