#ifndef Matrix_h
#define Matrix_h

#include "../constants/app.h"
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

#endif
