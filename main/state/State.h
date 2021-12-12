#pragma once

class State {
   public:
    virtual void setup() = 0;
    virtual void handle() = 0;
    virtual void cleanup() = 0;

    State() {}

    virtual ~State() {}
};
