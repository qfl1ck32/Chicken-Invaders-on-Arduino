#include "./globals.h"

#include "../constants/app.h"

StateManager stateManager = StateManager();

LCD *lcd = new LCD(RS, enable, d4, d5, d6, d7, contrast, backlight);

Joystick joystick = Joystick(pinSW, pinX, pinY);

NameSelector *nameSelector = new NameSelector(lcd, 1);

Menu menu = Menu(lcd);

Button button = Button(buttonPin);

Matrix *matrix = new Matrix(dinPin, clockPin, loadPin, 1, matrixRows, matrixCols);

Leaderboard leaderboard = Leaderboard();

Buzzer *songBuzzer = new Buzzer(songBuzzerPin);
Buzzer *gameSoundsBuzzer = new Buzzer(gameSoundsBuzzerPin);

GameEngine *gameEngine = new GameEngine(MATRIX_ROWS, MATRIX_COLUMNS);

GraphicsEngine graphicsEngine = GraphicsEngine(matrix);

GameStatus gameStatus = GameStatus(lcd);

Game game = Game();

void menuGoUp() {
    menu.goUp();
}

void menuGoDown() {
    menu.goDown();
}

void menuSelect() {
    menu.select();
}

void initialiseRandomSeed() {
    static const byte unusedPin = 0;
    randomSeed(analogRead(unusedPin));
}

bool getUsesMusic() {
    static bool defaultValue = true;

    byte value = EEPROM.read(EEPROM_MUSIC_PLAYING_INDEX);

    return value == EEPROM_MISSING_VALUE ? defaultValue : value == 1;
}

bool usesMusic = getUsesMusic();

const char backMessage[] PROGMEM = "Back";

const char increaseMessage[] PROGMEM = "Increase";
const char decreaseMessage[] PROGMEM = "Decrease";

const char pressXToContinueMessage[] PROGMEM = "Press X to continue.";

char *readStringFromPROGMEM(const char *progmemString) {
    byte length = strlen_P(progmemString);

    char *ans = new char[length + 1];

    memcpy_P(ans, progmemString, length);

    ans[length] = '\0';

    return ans;
}

char **readArrayOfStringsFromPROGMEM(const char *const *progmemArray, int length) {
    char **arr = new char *[length];

    for (byte i = 0; i < length; ++i) {
        char *str = readStringFromPROGMEM(*&progmemArray[i]);

        arr[i] = str;
    }

    return arr;
}

uint64_t readImageFromPROGMEM(const uint64_t *image) {
    uint64_t buffer;

    memcpy_P(&buffer, *&image, 8);

    return buffer;
}
