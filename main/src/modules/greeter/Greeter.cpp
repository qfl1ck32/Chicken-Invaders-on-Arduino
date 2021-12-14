#include "./Greeter.h"

void Greeter::run() {
    this->lcd->printOnRow(this->greeting, 0);
    this->lcd->printOnRow(this->introMessage, 1);

    if (this->delayer.canRun()) {
        this->lcd->scrollRow(1);
    }
}
