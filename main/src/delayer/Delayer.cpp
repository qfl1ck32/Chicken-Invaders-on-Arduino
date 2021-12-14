#include "./Delayer.h"

bool Delayer::canRun() {
    unsigned long currentTime = millis();

    bool canRun = currentTime - this->lastTime >= interval;

    if (canRun) {
        this->lastTime = currentTime;

        this->isInCooldown = false;

        return true;
    }

    this->isInCooldown = true;

    return false;
}

void Delayer::updateInterval(unsigned long newInterval) {
    this->interval = newInterval;
}