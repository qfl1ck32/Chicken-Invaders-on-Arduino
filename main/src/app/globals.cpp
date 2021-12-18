#include "./globals.h"

#include "../constants/app.h"
#include "./states/MainMenuState/MainMenuState.h"
#include "./states/SettingsMenuState/SettingsMenuState.h"

StateManager stateManager = StateManager();

LCD *lcd = new LCD(RS, enable, d4, d5, d6, d7, contrast, backlight);

Joystick joystick = Joystick(pinSW, pinX, pinY);

Menu menu = Menu(lcd);

Button button = Button(buttonPin);

Matrix *matrix = new Matrix(dinPin, clockPin, loadPin, 1, matrixRows, matrixCols);

Buzzer *songBuzzer = new Buzzer(songBuzzerPin);
Buzzer *gameSoundsBuzzer = new Buzzer(gameSoundsBuzzerPin);

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
    static const int8_t unusedPin = 0;
    randomSeed(analogRead(unusedPin));
}

bool getUsesMusic() {
    static bool defaultValue = true;

    int8_t value = EEPROM.read(EEPROM_MUSIC_PLAYING_INDEX);

    return value == 255 ? defaultValue : value == 1;
}

bool usesMusic = getUsesMusic();

uint8_t level = MIN_LEVEL;
uint8_t settingsLevel = level;

void setLevel(uint8_t _level) {
    if (_level < MIN_LEVEL || _level > MAX_LEVEL) return;

    level = _level;
}

void setSettingsLevel(uint8_t _level) {
    if (_level < MIN_LEVEL || _level > MAX_LEVEL) return;

    settingsLevel = _level;
}

void goToSettingsMenu() {
    stateManager.changeState<SettingsMenuState>();
}

void goToMainMenu() {
    stateManager.changeState<MainMenuState>();
}

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

    for (unsigned char i = 0; i < length; ++i) {
        PGM_P word = (PGM_P)pgm_read_word(&(progmemArray[i]));
        size_t length = strlen_P(word);

        char *buffer = new char[length + 1];

        strncpy_P(buffer, word, length);

        buffer[length] = '\0';

        arr[i] = buffer;
    }
    return arr;
}

uint64_t readImageFromPROGMEM(const uint64_t *image) {
    uint64_t buffer;

    memcpy_P(&buffer, *&image, 8);

    return buffer;
}