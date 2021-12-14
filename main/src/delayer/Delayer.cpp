#include "./Delayer.h"

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