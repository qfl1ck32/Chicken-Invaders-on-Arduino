#include "./Matrix.h"

Matrix::Matrix(int dataPin, int clkPin, int csPin, int numDevices, int8_t rows, int8_t columns) : LedControl(dataPin, clkPin, csPin, numDevices) {
    static int8_t defaultIntensity = 8;

    this->rows = rows;
    this->columns = columns;

    int8_t savedIntensity = EEPROM.read(EEPROM_MATRIX_INTENSITY_INDEX);

    this->intensity = savedIntensity == EEPROM_MISSING_VALUE ? defaultIntensity : savedIntensity;

    this->increaseIntensity(0);
}

void Matrix::increaseIntensity(short amount) {
    this->intensity = constrain(this->intensity + amount, 0, 15);

    this->setIntensity(0, this->intensity);

    EEPROM.write(EEPROM_MATRIX_INTENSITY_INDEX, this->intensity);
}

void Matrix::setup() {
    this->shutdown(0, false);
    this->clearDisplay(0);
}

void Matrix::setLed(int addr, int row, int column, boolean state) {
    LedControl::setLed(addr, this->columns - column - 1, row, state);
}

void Matrix::setAllLeds(bool val) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this->setLed(0, i, j, val);
        }
    }
}

void Matrix::displayImage(uint64_t image) {
    for (int row = 0; row < this->rows; ++row) {
        int8_t rowint8_t = (image >> row * this->columns) & 0xFF;

        for (int column = 0; column < this->columns; ++column) {
            this->setLed(0, row, column, bitRead(rowint8_t, column));
        }
    }
}
