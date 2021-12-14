#pragma once

class Buzzer {
   public:
    byte pin;

    Buzzer(byte pin) {
        this->pin = pin;
    }

    void buzz(unsigned int frequency, unsigned long duration) {
        tone(this->pin, frequency, duration);
    }

    void stop() {
        noTone(this->pin);
    }
};
