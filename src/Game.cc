#include "Game.hh"

Game::Game()
{

}

void Game::Start()
{

}

const char* Game::getNom() const
{
  return _nom;
}

const char* Game::getDesc() const
{
  return _desc;
}

const uint16_t* Game::getIcon() const
{
  return BITMAP_GAME_ICON_REACTIONTIME;
}

int Game::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  Serial.println(_nom);
  return 0;
}