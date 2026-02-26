#include "GameSnake.hh"

GameSnake::GameSnake()
{

}

void GameSnake::Start()
{

}

const char* GameSnake::getNom() const
{
  return _nom;
}

const char* GameSnake::getDesc() const
{
  return _desc;
}

const uint16_t* GameSnake::getIcon() const
{
  return BITMAP_GAME_ICON_SPAMCLICK;
}

int GameSnake::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long elapsed)
{
  return 0;
}