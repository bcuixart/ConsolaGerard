#ifndef GAMEAMONGUS_HH 
#define GAMEAMONGUS_HH

#include "Game.hh"
#include "Menu.hh"

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
    void Update_RevealCorrect(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    void Update_RevealIncorrect(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    void DrawCupAtPosition(int x);
    void DrawAmongusTwerk();

    const char* _nom = "Among Us";
    const char* _desc = "Troba el ninot  de l'Among Us   trapella que    s'ha amagat!";

    enum GameState {
      START,
      ROUNDTITLE,
      ROUNDMOVEMENT,
      CHOOSING,
      REVEAL,
      REVEAL_CORRECT,
      REVEAL_INCORRECT
    };
    GameState gameState;

    unsigned char correctCup = 0;
    unsigned char selectedCup = 0;
    bool hasChangedSelectedJoystick = false;

    unsigned long stateElapsed = 0;
    unsigned long waitDuration = 0;

    unsigned int round;

    unsigned int roundNumMovements = 0;
    unsigned char roundMovement = 0;
    float roundMovementDuration = 0;
    float roundTotalDuration = 0;
    float roundTotalElapsed = 0;
    bool roundReachedHalfway = false;

    float amongUsTwerkPosition = 0;
    float amongUsTwerkLastDrawnPosition = 0;
    float amongUsTwerkFrame = 0;

    bool thisRoundHasTwerk = false;
};

#endif