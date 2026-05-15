#ifndef GAMEREACTIONTIME_HH 
#define GAMEREACTIONTIME_HH

#include "Game.hh"

#define JOYSTICK_SELECT_BOUND_LOW 100
#define JOYSTICK_SELECT_BOUND_HIGH 924

class GameReactionTime : public Game
{
  public:
    GameReactionTime();

    virtual void Start();
    virtual int Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    virtual const char* getNom() const;
    virtual const char* getDesc() const;
    virtual const PalettedBitmap* getIcon() const;

  private:
    const char* _nom = "Vaquers";
    const char* _desc = "Dispara el teu  rival abans que ell et dispari atu!";
};

#endif