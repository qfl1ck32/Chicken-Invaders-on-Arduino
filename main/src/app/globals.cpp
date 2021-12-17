#include "./globals.h"

#include "../constants/app.h"

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

void setLevel(uint8_t _level) {
    if (_level < MIN_LEVEL || _level > MAX_LEVEL) return;

    level = _level;
}

const char backMessage[] PROGMEM = "Back";

const char increaseMessage[] PROGMEM = "Increase";
const char decreaseMessage[] PROGMEM = "Decrease";

const char pressXToContinueMessage[] PROGMEM = "Press X to continue.";

void readFromPROGMEM(const char progmemPointer[], char *buffer, int length) {
    for (int i = 0; i < length; ++i) {
        buffer[i] = (char)pgm_read_byte_near(progmemPointer + i);
    }

    buffer[length + 1] = '\0';
}

uint64_t readImageFromPROGMEM(const uint64_t *image) {
    uint64_t buffer;

    memcpy_P(&buffer, *&image, 8);

    return buffer;
}
