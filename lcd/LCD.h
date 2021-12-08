#pragma once

#include "../serial/printer/SerialPrinter.h"
#include "../strings/utils.h"

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

        this->contrast = 0;

        this->backlight = 0;

        this->changeContrast(100);
        this->changeBacklight(50);
    }

    void changeContrast(int);
    void changeBacklight(int);

    void printOnRow(String str, int row, int startAtColumn);
    void printOnRowAndColumn(char, int, int, bool);
    void setup(short, short);
    void scrollDisplayLeft();

    void scrollRow(int);

    void clearRow(int);
};

void LCD::changeContrast(int value) {
    this->contrast = constrain(this->contrast + value, 20, 240);

    analogWrite(this->contrastPin, this->contrast);
}

void LCD::changeBacklight(int value) {
    this->backlight = constrain(this->backlight + value, 10, 140);

    analogWrite(this->backlightPin, this->backlight);
}

void LCD::printOnRow(String str, int row, int startAtColumn = 0) {
    String current = this->lastStrings[row].substring(startAtColumn, startAtColumn + str.length());

    if (current == str) {
        return;
    }

    // show("Current: '", current, "', replace: '", str, "', sunt egale: ", current == str, ", start at: ", startAtColumn);

    // FIXME: not working how it's supposed to
    if (this->lastStrings[row].length() <= startAtColumn) {
        // show("Intra in primul!");
        this->lastStrings[row].concat(str);
    } else {
        // show("Intra in al doile!");
        this->lastStrings[row].replace(current, str);
    }

    this->clearRow(row);

    this->setCursor(startAtColumn, row);

    this->print(str);

    this->scrollOffsets[row] = 0;
}

void LCD::scrollRow(int row) {
    String word = this->lastStrings[row];

    int scrollOffset = this->scrollOffsets[row];

    this->setCursor(0, row);

    String wordToShow = "";

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