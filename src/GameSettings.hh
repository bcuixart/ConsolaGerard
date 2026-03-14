#ifndef GAMESETTINGS_HH 
#define GAMESETTINGS_HH

#include "Game.hh"
#include "Menu.hh"

class GameSettings : public Game
{
  public:
    GameSettings(const MenuTheme* menuThemes);

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

    void DrawScreenSettingSelection() const;
    void DrawScreenVolume() const;
    void DrawScreenName() const;
    void DrawScreenTheme() const;

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

    unsigned char _settingSelected = 0;

    unsigned long _joystickSelectedHeldTime = 0;

    const MenuTheme* menuThemes;
};

#endif