#ifndef GAME_HH 
#define GAME_HH

#include <Arduino.h>
#include "Screen.hh"
#include "Audio.hh"

class Game
{
  public:
    Game();

    virtual void Start();
    virtual int Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    virtual const char* getNom() const;
    virtual const char* getDesc() const;
    virtual const uint16_t* getIcon() const;

  private:
    const char* _nom = "JOC";
    const char* _desc = "DESCRIPCIO";
};

#endif