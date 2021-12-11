#pragma once

#include <LiquidCrystal.h>

typedef void (*HandlerFunction)();

#define EEPROM_MATRIX_INTENSITY_INDEX 0
#define EEPROM_LCD_BACKLIGHT_INDEX 1
#define EEPROM_LCD_CONTRAST_INDEX 2
#define EEPROM_LEADERBOARD_START_INDEX 3

#include "../button/Button.h"
#include "../constants/pins.h"
#include "../joystick/Joystick.h"
#include "../lcd/LCD.h"
#include "../matrix/Matrix.H"
#include "../menu/Menu.h"
#include "../modules/greeter/Greeter.h"
#include "../modules/leaderboard/Leaderboard.h"
#include "../modules/name-selection/NameSelector.h"
#include "../state-manager/StateManager.h"
#include "./states/constants.h"

StateManager *stateManager = new StateManager();

LCD *lcd = new LCD(RS, enable, d4, d5, d6, d7, contrast, backlight);

Joystick *joystick = new Joystick(pinSW, pinX, pinY);

NameSelector *nameSelector = new NameSelector(lcd, 1);

Menu *menu = new Menu(lcd);

void menuGoUp() {
    menu->goUp();
}

void menuGoDown() {
    menu->goDown();
}

void menuSelect() {
    menu->select();
}

Button *button = new Button(buttonPin);

Greeter *greeter = new Greeter(lcd, "Welcome!", "Press X to continue.");

Matrix *matrix = new Matrix(dinPin, clockPin, loadPin, 1, matrixRows, matrixCols);

Leaderboard *leaderboard = new Leaderboard();

#include "../game-engine/GameEngine.h"

GameEngine *gameEngine = new GameEngine(matrix);

#include "../graphics-engine/GraphicsEngine.h"

GraphicsEngine *graphicsEngine = new GraphicsEngine(matrix);

#include "../spaceship/Spaceship.h"

Spaceship *spaceship = 0;

#include "../modules/game-status/GameStatus.h"

GameStatus *gameStatus = new GameStatus(lcd);

#include "./states/PlayingState.h"

PlayingState *playingState = new PlayingState(playingStateId);
