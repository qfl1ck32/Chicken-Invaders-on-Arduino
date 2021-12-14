#ifndef globals_h
#define globals_h

#include <LiquidCrystal.h>

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
#include "../modules/greeter/Greeter.h"
#include "../modules/leaderboard/Leaderboard.h"
#include "../modules/name-selection/NameSelector.h"
#include "../state-manager/StateManager.h"
#include "./typedefs.h"

extern StateManager *stateManager;

extern LCD *lcd;

extern Joystick *joystick;

extern NameSelector *nameSelector;

extern Menu *menu;

extern void menuGoUp();

extern void menuGoDown();

extern void menuSelect();

extern Button *button;

extern Greeter *greeter;

extern Matrix *matrix;

extern Leaderboard *leaderboard;

extern Buzzer *songBuzzer;

extern Buzzer *gameSoundsBuzzer;

extern GameEngine *gameEngine;

extern GraphicsEngine *graphicsEngine;

extern GameStatus *gameStatus;

#endif
