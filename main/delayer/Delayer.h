#pragma once

class Delayer {
   public:
    unsigned long lastTime = 0;

    unsigned long interval;

    bool isInCooldown = false;

    Delayer(unsigned long interval) {
        this->interval = interval;
    }

    bool canRun();

    void updateInterval(unsigned long);
};

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