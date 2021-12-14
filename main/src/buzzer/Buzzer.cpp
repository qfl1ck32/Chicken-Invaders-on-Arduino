#include "./Buzzer.h"

Buzzer::Buzzer(byte pin) {
    this->pin = pin;
}

void Buzzer::buzz(unsigned int frequency, unsigned long duration) {
    tone(this->pin, frequency, duration);
}

void Buzzer::stop() {
    noTone(this->pin);
}
