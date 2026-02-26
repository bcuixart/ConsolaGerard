#ifndef MENU_HH 
#define MENU_HH

#include "Arduino.h"
#include "Screen.hh"
#include "Audio.hh"
#include "Game.hh"

void StartMenu(Game** games, const int numGames);

int UpdateMenu(const unsigned int joystickY, const unsigned long elapsed, unsigned char* selectedGame, Game** games, const int numGames);

void ChangeMenuDisplay(unsigned char selectedGame, Game** games, const int numGames);

#endif