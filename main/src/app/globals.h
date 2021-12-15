#ifndef globals_h
#define globals_h

#include "../button/Button.h"
#include "../buzzer/Buzzer.h"
#include "../constants/pins.h"
#include "../game-engine/GameEngine.h"
#include "../graphics-engine/GraphicsEngine.h"
#include "../joystick/Joystick.h"
#include "../lcd/LCD.h"
#include "../matrix/Matrix.H"
#include "../menu/Menu.h"
#include "../modules/game-status/GameStatus.h"
#include "../modules/game/Game.h"
#include "../modules/leaderboard/Leaderboard.h"
#include "../modules/name-selection/NameSelector.h"
#include "../state-manager/StateManager.h"
#include "./typedefs.h"

// TODO: move
#define aboutMenuStateId 0
#define gameOverStateId 1
#define leaderboardStateId 2
#define mainMenuStateId 3
#define nameSelectionStateId 4
#define playingStateId 5
#define settingsLCDMenuStateId 6
#define settingsMatrixMenuStateId 7
#define settingsMenuStateId 8
#define welcomeStateId 9
#define youWonStateId 10
#define settingsLevelMenuStateId 11

extern StateManager stateManager;

extern LCD *lcd;

extern Joystick joystick;

extern NameSelector *nameSelector;

extern Menu menu;

extern void menuGoUp();

extern void menuGoDown();

extern void menuSelect();

extern Button button;

extern Matrix *matrix;

extern Leaderboard leaderboard;

extern Buzzer *songBuzzer;

extern Buzzer *gameSoundsBuzzer;

extern GameEngine *gameEngine;

extern GraphicsEngine graphicsEngine;

extern GameStatus gameStatus;

extern Game game;

#endif
