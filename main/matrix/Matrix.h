#pragma once

#include "EEPROM.h"
#include "LedControl.h"

class Matrix : public LedControl {
   public:
    byte rows;
    byte columns;

    byte intensity;

    Matrix(int dataPin, int clkPin, int csPin, int numDevices, byte rows, byte columns) : LedControl(dataPin, clkPin, csPin, numDevices) {
        this->rows = rows;
        this->columns = columns;

        // TODO: addr
        this->setIntensity(0, 15);

        byte savedIntensity = EEPROM.read(EEPROM_MATRIX_INTENSITY_INDEX);

        // FIXME: hackish
        this->intensity = savedIntensity == 255 ? 8 : savedIntensity;

        this->increaseIntensity(0);
    }

    void setup();

    void setLed(int, int, int, boolean);

    void clear();

    void increaseIntensity(short);
};

void Matrix::increaseIntensity(short amount) {
    this->intensity = constrain(this->intensity + amount, 0, 15);

    // TODO: addr
    this->setIntensity(0, this->intensity);

    EEPROM.write(EEPROM_MATRIX_INTENSITY_INDEX, this->intensity);
}

void Matrix::setup() {
    // TODO: addr
    this->shutdown(0, false);
    this->clearDisplay(0);
}

void Matrix::setLed(int addr, int row, int column, boolean state) {
    LedControl::setLed(addr, this->columns - column - 1, row, state);
}

// TODO: addr!!!
void Matrix::clear() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this->setLed(0, i, j, false);
        }
    }
}
