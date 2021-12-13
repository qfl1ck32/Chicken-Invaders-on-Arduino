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

    void printOnRow(const char *msg, int row, int startAtColumn, bool resetPreviousString);
    void setup(short, short);
    void scrollDisplayLeft();

    void scrollRow(int row, int skip);

    void clearRow(int, bool);
    void clearRow(int, int, bool);
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

void LCD::printOnRow(const char *msg, int row, int startAtColumn = 0, bool resetPreviousString = true) {
    short messageLength = strlen(msg);

    short stringLength = strlen(this->lastStrings[row]);

    if (stringLength < startAtColumn + messageLength || strncmp(this->lastStrings[row] + startAtColumn, msg, messageLength) != 0 && resetPreviousString) {
        const int newLength = startAtColumn + messageLength;

        char *newString = new char[newLength + 1];

        for (int i = stringLength; i < newLength; ++i) {
            newString[i] = ' ';
        }

        newString[newLength] = '\0';

        if (!resetPreviousString) {
            strncpy(newString, this->lastStrings[row], stringLength);
        }

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

    short numberOfCharsToDisplay = min(strlen(msg), this->columns);

    char toDisplay[numberOfCharsToDisplay + 1];

    strncpy(toDisplay, msg, numberOfCharsToDisplay);

    toDisplay[numberOfCharsToDisplay] = '\0';

    this->print(toDisplay);

    this->scrollOffsets[row] = 0;
}

void LCD::scrollRow(int row, int skip = 0) {
    char *str = this->lastStrings[row] + skip;

    if (this->scrollOffsets[row] == strlen(str) + this->columns - skip) {
        this->scrollOffsets[row] = 0;
        return;
    }

    // TODO: be smarter, only turn off positions that are currently used
    this->clearRow(row, skip, false);

    if (this->scrollOffsets[row] < strlen(str)) {
        char *msg = str + this->scrollOffsets[row];

        this->setCursor(skip, row);
        this->print(msg);
    }

    else {
        int startAt = this->columns - this->scrollOffsets[row] + strlen(str) - 1;
        int numberOfCharsToDisplay = min(strlen(str), this->columns - startAt + 1);

        char toDisplay[numberOfCharsToDisplay + 1];

        strncpy(toDisplay, str, numberOfCharsToDisplay);

        toDisplay[numberOfCharsToDisplay] = '\0';

        this->setCursor(startAt, row);

        this->print(toDisplay);
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
    this->clearRow(row, 0, deleteLastString);
}

void LCD::clearRow(int row, int startAtColumn, bool deleteLastString = false) {
    for (int column = startAtColumn; column < this->columns; ++column) {
        this->setCursor(column, row);
        this->print(" ");
    }

    if (deleteLastString) {
        delete[] this->lastStrings[row];

        this->lastStrings[row] = new char[1];

        this->lastStrings[row][0] = '\0';
    }
}
