#ifndef LCD_h
#define LCD_h

#include <avr/pgmspace.h>

#include "../constants/app.h"
#include "Arduino.h"
#include "EEPROM.h"
#include "LiquidCrystal.h"

class LCD : public LiquidCrystal {
   public:
    byte rows;
    byte columns;

    byte contrastPin;
    byte contrast;

    byte backlightPin;
    byte backlight;

    char **lastStrings;
    byte *scrollOffsets;

    bool shouldClearRowOnPrint;

    LCD(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, int, int);

    void changeContrast(byte);
    void changeBacklight(byte);

    void printOnRow(const char *, byte, byte, bool);
    void printOnRow(const char *, byte, byte);
    void printOnRow(const char *, byte);

    // void printOnRowAndColumn(char, int, int, bool);

    void setup(byte, byte);
    void scrollDisplayLeft();

    void scrollRow(byte row, byte skip);
    void scrollRow(byte row);

    void clearRow(byte, bool);
    void clearRow(byte, byte, bool);

    void createChar(uint8_t, const byte *);
};

#endif
