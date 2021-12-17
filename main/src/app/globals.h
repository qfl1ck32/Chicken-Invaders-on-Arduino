#ifndef globals_h
#define globals_h

#include "../button/Button.h"
#include "../buzzer/Buzzer.h"
#include "../constants/pins.h"
#include "../game-engine/GameEngine.h"
#include "../joystick/Joystick.h"
#include "../lcd/LCD.h"
#include "../matrix/Matrix.H"
#include "../menu/Menu.h"
#include "../state-manager/StateManager.h"
#include "./typedefs.h"

extern StateManager stateManager;

extern LCD *lcd;

extern Joystick joystick;

extern Menu menu;

extern void menuGoUp();

extern void menuGoDown();

extern void menuSelect();

extern Button button;

extern Matrix *matrix;

extern Buzzer *songBuzzer;

extern Buzzer *gameSoundsBuzzer;

extern bool usesMusic;

extern uint8_t level;

extern void setLevel(uint8_t);

extern void initialiseRandomSeed();

extern const char backMessage[];

extern const char increaseMessage[];
extern const char decreaseMessage[];
extern const char pressXToContinueMessage[];

extern void readFromPROGMEM(const char[], char *, int);
extern uint64_t readImageFromPROGMEM(const uint64_t *);

#endif
