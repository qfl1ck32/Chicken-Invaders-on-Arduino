#include "../../delayer/Delayer.h"

class Greeter {
   public:
    LCD *lcd;
    const char *greeting;
    const char *introMessage;

    Delayer delayer = Delayer(350);

    Greeter(LCD *lcd, const char *greeting, const char *introMessage) {
        this->lcd = lcd;
        this->greeting = greeting;
        this->introMessage = introMessage;
    }

    void run();
};

void Greeter::run() {
    this->lcd->printOnRow(this->greeting, 0);
    this->lcd->printOnRow(this->introMessage, 1);

    if (this->delayer.canRun()) {
        this->lcd->scrollRow(1);
    }
}