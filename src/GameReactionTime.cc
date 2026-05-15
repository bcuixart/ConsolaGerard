#include "GameReactionTime.hh"

GameReactionTime::GameReactionTime()
{

}

void GameReactionTime::Start()
{
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

int GameReactionTime::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  return 0;
}