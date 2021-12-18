#ifndef LCD_h
#define LCD_h

#include <avr/pgmspace.h>

#include "../constants/app.h"
#include "Arduino.h"
#include "EEPROM.h"
#include "LiquidCrystal.h"

class LCD : public LiquidCrystal {
   public:
    int8_t rows;
    int8_t columns;

    int8_t contrastPin;
    int8_t contrast;

    int8_t backlightPin;
    int8_t backlight;

    char **lastStrings;
    int8_t *scrollOffsets;

    bool shouldClearRowOnPrint;

    LCD(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, int, int);

    void changeContrast(int8_t);
    void changeBacklight(int8_t);

    void printOnRow(const char *, int8_t, int8_t, bool);
    void printOnRow(const char *, int8_t, int8_t);
    void printOnRow(const char *, int8_t);

    // void printOnRowAndColumn(char, int, int, bool);

    void setup(int8_t, int8_t);
    void scrollDisplayLeft();

    void scrollRow(int8_t row, int8_t skip);
    void scrollRow(int8_t row);

    void clearRow(int8_t, bool);
    void clearRow(int8_t, int8_t, bool);

    void createChar(uint8_t, const byte *);
};

#endif
