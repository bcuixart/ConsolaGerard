#ifndef GAMESNAKE_HH 
#define GAMESNAKE_HH

#include "Game.hh"

class GameSnake : public Game
{
  public:
    GameSnake();

    virtual void Start();
    virtual int Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    virtual const char* getNom() const;
    virtual const char* getDesc() const;
    virtual const PalettedBitmap* getIcon() const;

  private:
    const char* _nom = "Snake";
    const char* _desc = "Made by Amat or smth";
};

#endif