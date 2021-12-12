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

    String *lastStrings;
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

    void printOnRow(String str, int row, int startAtColumn);
    void printOnRowAndColumn(char, int, int, bool);
    void setup(short, short);
    void scrollDisplayLeft();

    void scrollRow(int row, int skip);

    void clearRow(int);
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

void LCD::printOnRow(String str, int row, int startAtColumn = 0) {
    String current = this->lastStrings[row].substring(startAtColumn, startAtColumn + str.length());

    if (current == str) {
        return;
    }

    // FIXME: not working how it's supposed to
    if (this->lastStrings[row].length() <= startAtColumn) {
        this->lastStrings[row].concat(str);
    } else {
        this->lastStrings[row].replace(current, str);
    }

    this->clearRow(row);

    this->setCursor(startAtColumn, row);

    this->print(str);

    this->scrollOffsets[row] = 0;
}

// TODO: implement the "skip" part
void LCD::scrollRow(int row, int skip = 0) {
    String word = this->lastStrings[row];

    int scrollOffset = this->scrollOffsets[row];

    this->setCursor(0, row);

    String wordToShow = "";

    show(word);

    // FIXME: inefficient?
    if (scrollOffset < word.length()) {
        wordToShow.concat(word.substring(scrollOffset));
        wordToShow.concat(generateEmptyString(word.length() - scrollOffset - 1));
    }

    else {
        wordToShow.concat(generateEmptyString(this->columns - scrollOffset + word.length()));
        wordToShow.concat(word);
        wordToShow.concat(generateEmptyString(this->columns - word.length()));
    }

    this->print(wordToShow);

    if (scrollOffset == word.length() + this->columns) {
        this->scrollOffsets[row] = -1;
    }

    this->scrollOffsets[row] += 1;
}

void LCD::printOnRowAndColumn(char chr, int row, int column, bool ignoreLastString = false) {
    if (this->lastStrings[row].charAt(column) == chr) return;

    if (!ignoreLastString) {
        this->lastStrings[row] = setCharAtSafe(this->lastStrings[row], chr, column);
    }

    this->setCursor(column, row);

    this->print(chr);
}

void LCD::setup(short rows, short columns) {
    LiquidCrystal::begin(columns, rows);

    this->lastStrings = new String[rows];
    this->scrollOffsets = new short[rows];

    this->rows = rows;
    this->columns = columns;

    for (size_t i = 0; i < rows; ++i) {
        this->lastStrings[i] = "";
        this->scrollOffsets[i] = 0;
    }
}

void LCD::scrollDisplayLeft() {
    for (int i = 0; i < this->rows; ++i) {
        this->lastStrings[i].remove(0);
    }

    LiquidCrystal::scrollDisplayLeft();
}

void LCD::clearRow(int row) {
    for (int column = 0; column < this->columns; ++column) {
        this->setCursor(column, row);
        this->print(" ");
    }
}