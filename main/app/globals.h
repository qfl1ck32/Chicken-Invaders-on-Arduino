#pragma once

#include <LiquidCrystal.h>

typedef void (*HandlerFunction)();

#define EEPROM_MATRIX_INTENSITY_INDEX 0
#define EEPROM_LCD_BACKLIGHT_INDEX 1
#define EEPROM_LCD_CONTRAST_INDEX 2
#define EEPROM_LEADERBOARD_START_INDEX 3

#include "../button/Button.h"
#include "../buzzer/Buzzer.h"
#include "../constants/pins.h"
#include "../game-engine/GameEngine.cpp"
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

const char *const pressXToContinue PROGMEM = "Press X to continue";

const char *const welcome PROGMEM = "Welcome!";

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

Greeter *greeter = new Greeter(lcd, welcome, pressXToContinue);

Matrix *matrix = new Matrix(dinPin, clockPin, loadPin, 1, matrixRows, matrixCols);

Leaderboard *leaderboard = new Leaderboard();

Buzzer *songBuzzer = new Buzzer(songBuzzerPin);
Buzzer *gameSoundsBuzzer = new Buzzer(gameSoundsBuzzerPin);

// TODO: constants
GameEngine *gameEngine = new GameEngine(8, 8);

GraphicsEngine *graphicsEngine = new GraphicsEngine(matrix);

GameStatus *gameStatus = new GameStatus(lcd);
