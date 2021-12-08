#pragma once

class State {
   public:
    char state;

    virtual void setup() = 0;
    virtual void handle() = 0;
    virtual void cleanup() = 0;

    State(char state) {
        this->state = state;
    }
};
