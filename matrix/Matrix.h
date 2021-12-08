#pragma once

#include "LedControl.h"

class Matrix : public LedControl {
   public:
    short rows;
    short columns;

    Matrix(int dataPin, int clkPin, int csPin, int numDevices, int rows, int columns) : LedControl(dataPin, clkPin, csPin, numDevices) {
        this->rows = rows;
        this->columns = columns;
    }

    void setup();

    void setLed(int, int, int, boolean);

    void clear();
};

void Matrix::setup() {
    this->shutdown(0, false);
    this->setIntensity(0, 2);
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
