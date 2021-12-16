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

    LCD(uint8_t rs, uint8_t enable,
        uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, int contrast, int backlight) : LiquidCrystal(rs, enable, d0, d1, d2, d3) {
        this->contrastPin = contrast;
        this->backlightPin = backlight;

        pinMode(this->contrastPin, OUTPUT);
        pinMode(this->backlightPin, OUTPUT);

        byte savedContrast = EEPROM.read(EEPROM_LCD_CONTRAST_INDEX);

        this->contrast = savedContrast == EEPROM_MISSING_VALUE ? 100 : savedContrast;

        byte savedBacklight = EEPROM.read(EEPROM_LCD_BACKLIGHT_INDEX);

        this->backlight = savedBacklight == EEPROM_MISSING_VALUE ? 50 : savedBacklight;

        this->changeContrast(0);
        this->changeBacklight(0);
    }

    void changeContrast(int);
    void changeBacklight(int);

    void printOnRow(const char *, int, int, bool);
    void printOnRow(const char *, int);

    void setup(byte, byte);
    void scrollDisplayLeft();

    void scrollRow(int row, int skip);
    void scrollRow(int row);

    void clearRow(int, bool);
    void clearRow(int, int, bool);

    void createChar(uint8_t, const byte *);
};

#endif
