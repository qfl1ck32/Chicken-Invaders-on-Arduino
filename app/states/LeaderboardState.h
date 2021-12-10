#pragma once

class LeaderboardState : public State {
   public:
    LeaderboardState(int state) : State(state) {
    }

    void setup() {
        HandlerFunction handlers[] = {LeaderboardState::goBack};

        menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

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

        menu->setMessages(messages, sizeof(messages) / sizeof(char *));

        joystick->setHandlerOnYAxisChangeUp(menuGoUp);
        joystick->setHandlerOnYAxisChangeDown(menuGoDown);

        joystick->setHandlerSwStateChange(menuSelect);
    }

    void handle() {
        menu->run();
        joystick->handleJoystickMovements();
    }

    void cleanup() {
        lcd->clear();

        joystick->clearHandlers();
    }

    static void goBack() {
        stateManager->changeState(mainMenuStateId);
    }
};
