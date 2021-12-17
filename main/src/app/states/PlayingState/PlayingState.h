#ifndef PlayingState_h
#define PlayingState_h

#include "../../../chicken/Chicken.h"
#include "../../../game-status/GameStatus.h"
#include "../../../graphics-engine/GraphicsEngine.h"
#include "../../../spaceship/Spaceship.h"
#include "../../../state/State.h"
#include "../../../unit/Unit.h"

#define PLAYING 0
#define WON 1
#define LOST 2

class PlayingState : public State {
   public:
    PlayingState();
    ~PlayingState();

    GraphicsEngine *graphicsEngine;
    GameStatus *gameStatus;

    uint8_t state;

    void setup();
    void handle();
    void cleanup();

    static Spaceship *spaceship;

    short score;

    unsigned long timeSinceLastStart;

    static int8_t maxLevel;

    bool needsInitialisation;

    void setSpaceship(int8_t, int8_t);

    void reset();

    void setupLevel();

    static void moveUp();

    static void moveRight();

    static void moveDown();

    static void moveLeft();

    static void attack();
};

#endif
