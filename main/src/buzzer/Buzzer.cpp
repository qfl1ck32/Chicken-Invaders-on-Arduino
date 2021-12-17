#include "./Buzzer.h"

Buzzer::Buzzer(int8_t pin) {
    this->pin = pin;
}

void Buzzer::buzz(unsigned int frequency, unsigned int duration) {
    tone(this->pin, frequency, duration);
}

void Buzzer::stop() {
    noTone(this->pin);
}
