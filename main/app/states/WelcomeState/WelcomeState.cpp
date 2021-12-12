#pragma once

#include "./WelcomeState.h"

#include "../MainMenuState/MainMenuState.cpp"

void WelcomeState::setup() {
    button->setOnStateChange(WelcomeState::moveToEnterYourNameState);
}

void WelcomeState::handle() {
    greeter->run();
}

void WelcomeState::cleanup() {
    button->clearHandler();
    lcd->clear();
}

void WelcomeState::moveToEnterYourNameState() {
    stateManager->changeState<MainMenuState>();
}
