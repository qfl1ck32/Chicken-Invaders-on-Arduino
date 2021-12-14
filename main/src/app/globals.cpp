#include "./globals.h"

#include "../constants/app.h"

const char *const pressXToContinue PROGMEM = "Press X to continue";

const char *const welcome PROGMEM = "Welcome!";

StateManager *stateManager = new StateManager();

LCD *lcd = new LCD(RS, enable, d4, d5, d6, d7, contrast, backlight);

Joystick *joystick = new Joystick(pinSW, pinX, pinY);

NameSelector *nameSelector = new NameSelector(lcd, 1);

Menu *menu = new Menu(lcd);

Button *button = new Button(buttonPin);

Greeter *greeter = new Greeter(lcd, welcome, pressXToContinue);

Matrix *matrix = new Matrix(dinPin, clockPin, loadPin, 1, matrixRows, matrixCols);

Leaderboard *leaderboard = new Leaderboard();

Buzzer *songBuzzer = new Buzzer(songBuzzerPin);
Buzzer *gameSoundsBuzzer = new Buzzer(gameSoundsBuzzerPin);

GameEngine *gameEngine = new GameEngine(MATRIX_ROWS, MATRIX_COLUMNS);

GraphicsEngine *graphicsEngine = new GraphicsEngine(matrix);

GameStatus *gameStatus = new GameStatus(lcd);

void menuGoUp() {
    menu->goUp();
}

void menuGoDown() {
    menu->goDown();
}

void menuSelect() {
    menu->select();
}