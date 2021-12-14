#include "./LCD.h"

const byte heartCharArray[8] PROGMEM = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000};

byte heartChar = 1;

void LCD::createChar(uint8_t location, const byte *charMap) {
    location &= 0x7;  // we only have 8 locations 0-7
    command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++) {
        write(pgm_read_byte_near(charMap++));  // reading from progmem
    }
}

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

void LCD::printOnRow(const char *msg, int row) {
    LCD::printOnRow(msg, row, 0, true);
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

void LCD::scrollRow(int row) {
    LCD::scrollRow(row, 0);
}

void LCD::setup(byte rows, byte columns) {
    LiquidCrystal::begin(columns, rows);

    this->lastStrings = new char *[rows];
    this->scrollOffsets = new byte[rows];

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
