#pragma once

#include "../serial/printer/SerialPrinter.h"
#include "../strings/utils.h"
#include "EEPROM.h"

byte heartCharArray[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000};

byte heartChar = 1;

class LCD : public LiquidCrystal {
   public:
    short rows;
    short columns;

    short contrastPin;
    short contrast;

    short backlightPin;
    short backlight;

    char **lastStrings;
    short *scrollOffsets;

    LCD(uint8_t rs, uint8_t enable,
        uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, int contrast, int backlight) : LiquidCrystal(rs, enable, d0, d1, d2, d3) {
        this->contrastPin = contrast;
        this->backlightPin = backlight;

        pinMode(this->contrastPin, OUTPUT);
        pinMode(this->backlightPin, OUTPUT);

        byte savedContrast = EEPROM.read(EEPROM_LCD_CONTRAST_INDEX);

        // TODO: "== 255" <=> "== EEPROM_MISSING_VALUE"
        this->contrast = savedContrast == 255 ? 100 : savedContrast;

        byte savedBacklight = EEPROM.read(EEPROM_LCD_BACKLIGHT_INDEX);

        this->backlight = savedBacklight == 255 ? 50 : savedBacklight;

        this->changeContrast(0);
        this->changeBacklight(0);
    }

    void changeContrast(int);
    void changeBacklight(int);

    void printOnRow(const char *msg, int row, int startAtColumn);
    void setup(short, short);
    void scrollDisplayLeft();

    void scrollRow(int row, int skip);

    void clearRow(int, bool);
};

void LCD::changeContrast(int value) {
    this->contrast = constrain(this->contrast + value, 20, 240);

    analogWrite(this->contrastPin, this->contrast);

    EEPROM.write(EEPROM_LCD_CONTRAST_INDEX, this->contrast);
}

void LCD::changeBacklight(int value) {
    this->backlight = constrain(this->backlight + value, 10, 140);

    analogWrite(this->backlightPin, this->backlight);

    EEPROM.write(EEPROM_LCD_BACKLIGHT_INDEX, this->backlight);
}

void LCD::printOnRow(const char *msg, int row, int startAtColumn = 0) {
    short messageLength = strlen(msg);

    short stringLength = strlen(this->lastStrings[row]);

    if (stringLength < startAtColumn + messageLength) {
        const int newLength = startAtColumn + messageLength;

        char *newString = new char[newLength];

        for (int i = stringLength; i < newLength; ++i) {
            newString[i] = ' ';
        }

        newString[newLength] = '\0';

        strncpy(newString, this->lastStrings[row], stringLength);

        delete[] this->lastStrings[row];

        this->lastStrings[row] = newString;
    }

    char *previous = (this->lastStrings[row] + startAtColumn);

    if (strncmp(previous, msg, messageLength) == 0) {
        return;
    }

    // TODO: why. you should only clear the interval left from the prev. message
    this->clearRow(row, false);

    strncpy(this->lastStrings[row] + startAtColumn, msg, messageLength);

    this->setCursor(startAtColumn, row);

    this->print(msg);

    this->scrollOffsets[row] = 0;
}

// TODO: implement the "skip" part
void LCD::scrollRow(int row, int skip = 0) {
    char *str = this->lastStrings[row];

    if (this->scrollOffsets[row] == strlen(str) + this->columns) {
        this->scrollOffsets[row] = 0;
    }

    // TODO: be smarter, only turn off positions that are currently used
    this->clearRow(row, false);

    if (this->scrollOffsets[row] < strlen(str)) {
        char *msg = str + this->scrollOffsets[row];

        this->setCursor(0, row);
        this->print(msg);
    }

    else {
        int numberOfCharsToShow = min(this->scrollOffsets[row] - strlen(str) + 1, strlen(str));
        int startAt = this->columns - this->scrollOffsets[row] + strlen(str) - 1;

        this->setCursor(startAt, row);
        this->print(str);
    }

    ++this->scrollOffsets[row];
}

void LCD::setup(short rows, short columns) {
    LiquidCrystal::begin(columns, rows);

    this->lastStrings = new char *[rows];
    this->scrollOffsets = new short[rows];

    this->rows = rows;
    this->columns = columns;

    for (size_t i = 0; i < rows; ++i) {
        // TODO: minimum size? works?
        this->lastStrings[i] = new char[1];

        this->lastStrings[i][0] = '\0';

        this->scrollOffsets[i] = 0;
    }
}

void LCD::clearRow(int row, bool deleteLastString = false) {
    for (int column = 0; column < this->columns; ++column) {
        this->setCursor(column, row);
        this->print(" ");
    }

    if (deleteLastString) {
        delete[] this->lastStrings[row];

        this->lastStrings[row] = new char[1];

        this->lastStrings[row][0] = '\0';
    }
}
