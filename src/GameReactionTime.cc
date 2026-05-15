#include "GameReactionTime.hh"

GameReactionTime::GameReactionTime()
{

}

void GameReactionTime::Start()
{
  gameState = START;

  drawPaletteBitmap(0, 0, BITMAP_GAME_REACTIONTIME_INTROANIMATION_000);
}

const char* GameReactionTime::getNom() const
{
  return _nom;
}

const char* GameReactionTime::getDesc() const
{
  return _desc;
}

const PalettedBitmap* GameReactionTime::getIcon() const
{
  return &BITMAP_GAME_ICON_REACTIONTIME;
}

void GameReactionTime::Update_Start(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) { timeForNextWord = random(3000, 10000); gameState = ROUNDWAIT; }
}

void GameReactionTime::Update_RoundWait(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  timeForNextWord -= elapsed;

  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) gameState = LOST;

  if (timeForNextWord <= 0) 
  {
    timeForNextWord = random(3000, 10000);

    int randomWord = random(0, 5);
    if (randomWord == 0) drawWrappedText("Foca!", 0, 10, 160, 128, 2, ST7735_WHITE);
    else if (randomWord == 1) drawWrappedText("Fira!", 0, 10, 160, 128, 2, ST7735_WHITE);
    else if (randomWord == 2) drawWrappedText("Ara!", 0, 10, 160, 128, 2, ST7735_WHITE);
    else if (randomWord == 3) drawWrappedText("Foc!", 0, 10, 160, 128, 2, ST7735_WHITE);
    else drawWrappedText("Dale!", 0, 10, 160, 128, 2, ST7735_WHITE);

    // Fosc, forn, floc, font, focaccia, juego, luego, fuelle, fuera, fiera, foco, foso


    if (randomWord == 3) gameState = FIREWAIT;
  }
}

void GameReactionTime::Update_RoundWaitTumbleweed(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{

}

void GameReactionTime::Update_FireWait(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) gameState = WON;
}

void GameReactionTime::Update_Lost(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  drawWrappedText("Gilipollas.", 0, 10, 160, 128, 2, ST7735_WHITE);
}

void GameReactionTime::Update_Won(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  drawWrappedText("Enohrabona. Has guanyat. Que be.", 0, 10, 160, 128, 2, ST7735_WHITE);
} 


int GameReactionTime::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  switch(gameState)
  {
    case START:
      Update_Start(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case ROUNDWAIT:
      Update_RoundWait(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case ROUNDWAITTUMBLEWEED:
      Update_RoundWaitTumbleweed(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);  
      break;
    case FIREWAIT:
      Update_FireWait(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case LOST:
      Update_Lost(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case WON:
      Update_Won(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
  }

  return 0;
}