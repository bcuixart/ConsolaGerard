#ifndef GAMEAMONGUS_HH 
#define GAMEAMONGUS_HH

#include "Game.hh"

#define COLOR_WALL 0x4bd0
#define COLOR_FLOOR 0x7d15

#define JOYSTICK_SELECT_BOUND_LOW 100
#define JOYSTICK_SELECT_BOUND_HIGH 924

class GameAmongUs : public Game
{
  public:
    GameAmongUs();

    virtual void Start();
    virtual int Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    virtual const char* getNom() const;
    virtual const char* getDesc() const;
    virtual const uint16_t* getIcon() const;

  private:
    void Update_Start(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    void Update_RoundTitle(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    void Update_RoundMovement(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    void Update_Choosing(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    void Update_Reveal(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    const char* _nom = "Among Us";
    const char* _desc = "Troba el ninot  de l'Among Us   trapella que    s'ha amagat!";

    enum GameState {
      START,
      ROUNDTITLE,
      ROUNDMOVEMENT,
      CHOOSING,
      REVEAL
    };
    GameState gameState;

    unsigned char correctCup = 0;
    unsigned char selectedCup = 0;
    bool hasChangedSelectedJoystick = false;
};

#endif