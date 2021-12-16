#include "Arduino.h"

#define EEPROM_MATRIX_INTENSITY_INDEX 0
#define EEPROM_LCD_BACKLIGHT_INDEX 1
#define EEPROM_MUSIC_PLAYING_INDEX 2
#define EEPROM_LCD_CONTRAST_INDEX 3

#define EEPROM_LEADERBOARD_START_INDEX 4

#define EEPROM_MISSING_VALUE 255

#define MAX_MESSAGES 5

#define BULLET_TYPE 0
#define CHICKEN_TYPE 1
#define EGG_TYPE 2
#define SPACESHIP_TYPE 3

#define KILL 1

#define MATRIX_ROWS 8
#define MATRIX_COLUMNS 8

#define aboutMenuStateId 0
#define gameOverStateId 1
#define leaderboardStateId 2
#define mainMenuStateId 3
#define nameSelectionStateId 4
#define playingStateId 5
#define settingsLCDMenuStateId 6
#define settingsMatrixMenuStateId 7
#define settingsMenuStateId 8
#define welcomeStateId 9
#define youWonStateId 10
#define settingsLevelMenuStateId 11
#define settingsSoundsMenuStateId 12

extern const byte heartCharArray[8];
extern byte heartChar;

#define INT_MAX 0x7FFF
