#include <Wire.h>

const int MPU = 0x68;

class Gyroscope {
   public:
    void setup();
};

void Gyroscope::setup() {
    Wire.begin();

    Wire.beginTransmission(MPU);

    Wire.write(0x6B);

    Write.write(0);

    Wire.endTransmission(true);
}
