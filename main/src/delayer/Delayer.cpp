#include "./Delayer.h"

Delayer::Delayer(unsigned int interval) {
    this->interval = interval;
}

Delayer::Delayer() {
    this->interval = 0;
}

bool Delayer::canRun() {
    unsigned int currentTime = millis();

    bool canRun = currentTime - this->lastTime >= interval;

    if (canRun) {
        this->lastTime = currentTime;

        this->isInCooldown = false;

        return true;
    }

    this->isInCooldown = true;

    return false;
}

void Delayer::updateInterval(unsigned int newInterval) {
    this->interval = newInterval;
}
