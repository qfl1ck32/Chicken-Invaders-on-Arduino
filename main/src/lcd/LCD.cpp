#include "./LCD.h"

#include "../constants/app.h"

LCD::LCD(uint8_t rs, uint8_t enable,
         uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, int contrast, int backlight) : LiquidCrystal(rs, enable, d0, d1, d2, d3) {
    this->contrastPin = contrast;
    this->backlightPin = backlight;

    pinMode(this->contrastPin, OUTPUT);
    pinMode(this->backlightPin, OUTPUT);

    int8_t savedContrast = EEPROM.read(EEPROM_LCD_CONTRAST_INDEX);

    this->contrast = savedContrast == EEPROM_MISSING_VALUE ? 100 : savedContrast;

    int8_t savedBacklight = EEPROM.read(EEPROM_LCD_BACKLIGHT_INDEX);

    this->backlight = savedBacklight == EEPROM_MISSING_VALUE ? 50 : savedBacklight;

    this->changeContrast(0);
    this->changeBacklight(0);

    this->shouldClearRowOnPrint = true;
}

void LCD::createChar(uint8_t location, const int8_t *charMap) {
    location &= 0x7;

    command(LCD_SETCGRAMADDR | (location << 3));

    for (int i = 0; i < 8; i++) {
        write(pgm_read_byte_near(charMap++));
    }
}

void LCD::changeContrast(int8_t value) {
    this->contrast = constrain(this->contrast + value, 20, 240);

    analogWrite(this->contrastPin, this->contrast);

    EEPROM.write(EEPROM_LCD_CONTRAST_INDEX, this->contrast);
}

void LCD::changeBacklight(int8_t value) {
    this->backlight = constrain(this->backlight + value, 10, 140);

    analogWrite(this->backlightPin, this->backlight);

    EEPROM.write(EEPROM_LCD_BACKLIGHT_INDEX, this->backlight);
}

void LCD::printOnRow(const char *msg, int8_t row, int8_t startAtColumn = 0, bool resetPreviousString = true) {
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

        delete this->lastStrings[row];

        this->lastStrings[row] = newString;
    }

    char *previous = (this->lastStrings[row] + startAtColumn);

    if (strncmp(previous, msg, messageLength) == 0) {
        return;
    }

    if (this->shouldClearRowOnPrint) {
        this->clearRow(row, false);
    }

    else {
        for (int column = startAtColumn; column < startAtColumn + max(stringLength, messageLength); ++column) {
            if (previous[column] != msg[column]) {
                this->setCursor(column, row);
                this->print(column >= messageLength ? ' ' : msg[column]);
            }
        }
    }

    strncpy(this->lastStrings[row] + startAtColumn, msg, messageLength);

    this->setCursor(startAtColumn, row);

    short numberOfCharsToDisplay = min(strlen(msg), this->columns);

    char toDisplay[numberOfCharsToDisplay + 1];

    strncpy(toDisplay, msg, numberOfCharsToDisplay);

    toDisplay[numberOfCharsToDisplay] = '\0';

    this->print(toDisplay);

    this->scrollOffsets[row] = 0;
}

void LCD::printOnRow(const char *msg, int8_t row, int8_t startAtColumn) {
    LCD::printOnRow(msg, row, startAtColumn, true);
}

void LCD::printOnRow(const char *msg, int8_t row) {
    LCD::printOnRow(msg, row, 0, true);
}

// TODO: this could have a refactorization tho, not dry enough
void LCD::scrollRow(int8_t row, int8_t skip = 0) {
    char *str = this->lastStrings[row] + skip;

    uint8_t length = strlen(str);

    if (this->scrollOffsets[row] == length + this->columns - skip) {
        this->scrollOffsets[row] = 0;
        return;
    }

    // TODO: only turn off positions that are currently used
    this->clearRow(row, skip, false);

    if (this->scrollOffsets[row] < length) {
        char *msg = str + this->scrollOffsets[row];

        int numberOfCharsToDisplay = min(strlen(msg), this->columns - skip);

        char toDisplay[numberOfCharsToDisplay + 1];

        strncpy(toDisplay, msg, numberOfCharsToDisplay);

        toDisplay[numberOfCharsToDisplay] = '\0';

        this->setCursor(skip, row);

        this->print(toDisplay);
    }

    else {
        int startAt = this->columns - this->scrollOffsets[row] + length - 1;
        int numberOfCharsToDisplay = min(length, this->columns - startAt + 1);

        char toDisplay[numberOfCharsToDisplay + 1];

        strncpy(toDisplay, str, numberOfCharsToDisplay);

        toDisplay[numberOfCharsToDisplay] = '\0';

        this->setCursor(startAt, row);

        this->print(toDisplay);
    }

    ++this->scrollOffsets[row];
}

void LCD::scrollRow(int8_t row) {
    LCD::scrollRow(row, 0);
}

void LCD::setup(int8_t rows, int8_t columns) {
    LiquidCrystal::begin(columns, rows);

    this->lastStrings = new char *[rows];
    this->scrollOffsets = new int8_t[rows];

    this->rows = rows;
    this->columns = columns;

    for (size_t i = 0; i < rows; ++i) {
        this->lastStrings[i] = new char[1];

        this->lastStrings[i][0] = '\0';

        this->scrollOffsets[i] = 0;
    }
}

void LCD::clearRow(int8_t row, bool deleteLastString = false) {
    this->clearRow(row, 0, deleteLastString);
}

void LCD::clearRow(int8_t row, int8_t startAtColumn, bool deleteLastString = false) {
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
