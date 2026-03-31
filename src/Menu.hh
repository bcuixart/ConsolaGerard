#ifndef MENU_HH 
#define MENU_HH

#include "Arduino.h"
#include "Screen.hh"
#include "Audio.hh"
#include "Game.hh"

#define MENU_THEME_COUNT 3

#define JOYSTICK_SELECT_BOUND_LOW 100
#define JOYSTICK_SELECT_BOUND_HIGH 924
#define JOYSTICK_SELECT_HOLD_TIME 200
#define JOYSTICK_SHORT_PRESS_MAX 300

struct MenuTheme {
    uint16_t backgroundColor;
    uint16_t highlightColor;
    uint16_t otherColor;
};

const MenuTheme menuThemes[MENU_THEME_COUNT] = {
    {ST77XX_WHITE, ST77XX_BLUE, ST77XX_BLACK},
    {ST77XX_BLACK, ST77XX_GREEN, ST77XX_WHITE},
    {ST77XX_YELLOW, ST77XX_RED, ST77XX_BLACK}
};

void StartMenu(Game** games, unsigned char* selectedGame,  const int numGames);

int UpdateMenu(const unsigned int joystickY, const unsigned long elapsed, unsigned char* selectedGame, Game** games, const int numGames);

#endif