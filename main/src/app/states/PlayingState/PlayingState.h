#ifndef PlayingState_h
#define PlayingState_h

#include "../../../chicken/Chicken.h"
#include "../../../game-status/GameStatus.h"
#include "../../../graphics-engine/GraphicsEngine.h"
#include "../../../leaderboard/Leaderboard.h"
#include "../../../spaceship/Spaceship.h"
#include "../../../state/State.h"
#include "../../../unit/Unit.h"
#include "../../states/MainMenuState/MainMenuState.h"
#include "../../states/NameSelectionState/NameSelectionState.h"

#define NOT_INITIALISED 0
#define PLAYING 1
#define WON 2
#define LOST 4

class PlayingState : public State {
   public:
    PlayingState();
    ~PlayingState();

    GraphicsEngine *graphicsEngine;
    GameStatus *gameStatus;
    Delayer *scrollDelayer;

    static Leaderboard *leaderboard;

    uint8_t lastNumberOfChickens;

    static uint8_t previousState;
    static uint8_t state;

    void setup();
    void handle();
    void cleanup();

    void play();
    void handleLostState();
    void handleWonState();

    void switchToWonState();
    void switchToLostState();

    void updateScore();

    static Spaceship *spaceship;

    static short score;

    unsigned long timeSinceLastStart;

    static int8_t maxLevel;

    bool needsInitialisation;

    void reset();

    void setupLevel();

    static void moveUp();

    static void moveRight();

    static void moveDown();

    static void moveLeft();

    static void attack();

    static void goToNextLevel();

    static void goToNextScreenAfterDeath();

    static void updateState(uint8_t);
};

#endif
