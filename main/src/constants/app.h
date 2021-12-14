#include "Arduino.h"

#define EEPROM_MATRIX_INTENSITY_INDEX 0
#define EEPROM_LCD_BACKLIGHT_INDEX 1
#define EEPROM_LCD_CONTRAST_INDEX 2
#define EEPROM_LEADERBOARD_START_INDEX 3

#define MAX_MESSAGES 5

#define BULLET_TYPE 0
#define CHICKEN_TYPE 1
#define EGG_TYPE 2
#define SPACESHIP_TYPE 3

#define KILL 1

extern const byte heartCharArray[8];
extern byte heartChar;