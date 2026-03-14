#include "Menu.hh"

unsigned long joystickSelectedHeldTime = 0;

int menuThemeSelected = 0;

void ChangeMenuDisplay(unsigned char selectedGame, Game** games, const int numGames);

void StartMenu(Game** games, unsigned char* selectedGame, const int numGames)
{
  readFromEEPROM(EEPROM_MENU_THEME_ADDRESS, &menuThemeSelected, 1);
  tft.fillScreen(menuThemes[menuThemeSelected].backgroundColor);

  tft.fillRect(13, 3, 34, 34, menuThemes[menuThemeSelected].otherColor);
  tft.fillRect(12, 46, 36, 36, menuThemes[menuThemeSelected].highlightColor);
  tft.fillRect(13, 90, 34, 34, menuThemes[menuThemeSelected].otherColor);

  tft.fillTriangle(29, 38, 34, 43, 24, 43, menuThemes[menuThemeSelected].highlightColor);
  tft.fillTriangle(24, 83, 34, 83, 29, 88, menuThemes[menuThemeSelected].highlightColor);

  playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_START);

  ChangeMenuDisplay(*selectedGame, games, numGames);
}

int UpdateMenu(const unsigned int joystickY, const unsigned long elapsed, unsigned char* selectedGame, Game** games, const int numGames)
{  
  if (joystickY < JOYSTICK_SELECT_BOUND_HIGH && joystickY > JOYSTICK_SELECT_BOUND_LOW) 
  {
    joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;
  }
  else if (joystickY >= JOYSTICK_SELECT_BOUND_HIGH) 
  {
    joystickSelectedHeldTime += elapsed;
    if (joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      joystickSelectedHeldTime = 0;
      *selectedGame = (*selectedGame + 1) % numGames;
      playAudio(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      ChangeMenuDisplay(*selectedGame, games, numGames);
    }
  } 
  else
  {
    joystickSelectedHeldTime += elapsed;
    if (joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      joystickSelectedHeldTime = 0;
      *selectedGame = (*selectedGame - 1 + numGames) % numGames;
      playAudio(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      ChangeMenuDisplay(*selectedGame, games, numGames);
    }
  }

  return 0;
}

void ChangeMenuDisplay(unsigned char selectedGame, Game** games, const int numGames)
{
  tft.fillRect(55, 46, 150, 100, menuThemes[menuThemeSelected].backgroundColor);

  drawWrappedText(games[selectedGame]->getNom(), 55, 46, 100, 100, 2, menuThemes[menuThemeSelected].highlightColor);
  drawWrappedText(games[selectedGame]->getDesc(), 55, 65, 100, 100, 1, menuThemes[menuThemeSelected].highlightColor);
  
  char prevGame = (selectedGame - 1 + numGames) % numGames;
  char nextGame = (selectedGame + 1) % numGames;
  tft.drawRGBBitmap(14, 48, games[selectedGame]->getIcon(), 32, 32);
  tft.drawRGBBitmap(14, 4, games[prevGame]->getIcon(), 32, 32);
  tft.drawRGBBitmap(14, 91, games[nextGame]->getIcon(), 32, 32);
}
