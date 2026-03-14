#ifndef GAMESETTINGS_HH 
#define GAMESETTINGS_HH

#include "Game.hh"

class GameSettings : public Game
{
  public:
    GameSettings();

    virtual void Start();
    virtual int Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    virtual const char* getNom() const;
    virtual const char* getDesc() const;
    virtual const uint16_t* getIcon() const;

  private:
    int Update_SettingSelection(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    int Update_Volume(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    int Update_Name(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);
    int Update_Theme(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed);

    const char* _nom = "Ajustar";
    const char* _desc = "Canvia la       configuracio    de la consola.";

    enum GameState {
      SETTING_SELECTION,
      VOLUME,
      NAME,
      THEME,
    };
    GameState gameState;

    unsigned char _currentVolume;
    char* _currentWelcomeName;
    unsigned char _currentMenuTheme;
};

#endif