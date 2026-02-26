#include "Menu.hh"

#define JOYSTICK_SELECT_BOUND_LOW 100
#define JOYSTICK_SELECT_BOUND_HIGH 924
#define JOYSTICK_SELECT_HOLD_TIME 200

float joystickSelectedHeldTime = 0;

void StartMenu(Game** games, unsigned char* selectedGame, const int numGames)
{
  tft.fillScreen(ST77XX_WHITE);

  tft.fillRect(13, 3, 34, 34, ST77XX_BLACK);
  tft.fillRect(12, 46, 36, 36, ST77XX_BLUE);
  tft.fillRect(13, 90, 34, 34, ST77XX_BLACK);

  tft.fillTriangle(29, 38, 34, 43, 24, 43, ST77XX_BLUE);
  tft.fillTriangle(24, 83, 34, 83, 29, 88, ST77XX_BLUE);

  ChangeMenuDisplay(0, games, numGames);
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
    if (joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) {
      joystickSelectedHeldTime = 0;
      *selectedGame = (*selectedGame + 1) % numGames;
      playAudio(AUDIO_FOLDER_MENU, AUDIO_FOLDER_MENU_CANVI_SELECCIO);
      ChangeMenuDisplay(*selectedGame, games, numGames);
    }
  } 
  else
  {
    joystickSelectedHeldTime += elapsed;
    if (joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) {
      joystickSelectedHeldTime = 0;
      *selectedGame = (*selectedGame - 1 + numGames) % numGames;
      playAudio(AUDIO_FOLDER_MENU, AUDIO_FOLDER_MENU_CANVI_SELECCIO);
      ChangeMenuDisplay(*selectedGame, games, numGames);
    }
  }

  return 0;
}

void ChangeMenuDisplay(unsigned char selectedGame, Game** games, const int numGames)
{
  tft.fillRect(55, 46, 150, 100, ST77XX_WHITE);

  drawWrappedText(games[selectedGame]->getNom(), 55, 46, 100, 100, 2, ST7735_BLUE);
  drawWrappedText(games[selectedGame]->getDesc(), 55, 65, 100, 100, 1, ST7735_BLUE);
  
  char prevGame = (selectedGame - 1 + numGames) % numGames;
  char nextGame = (selectedGame + 1) % numGames;
  tft.drawRGBBitmap(14, 48, games[selectedGame]->getIcon(), 32, 32);
  tft.drawRGBBitmap(14, 4, games[prevGame]->getIcon(), 32, 32);
  tft.drawRGBBitmap(14, 91, games[nextGame]->getIcon(), 32, 32);
}
