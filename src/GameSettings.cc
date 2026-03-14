#include "GameSettings.hh"

GameSettings::GameSettings(const MenuTheme* menuThemes) : menuThemes(menuThemes)
{

}

const char* GameSettings::getNom() const
{
  return _nom;
}

const char* GameSettings::getDesc() const
{
  return _desc;
}

const uint16_t* GameSettings::getIcon() const
{
  return BITMAP_GAME_ICON_AMONGUS;
}

void GameSettings::Start()
{
    gameState = SETTING_SELECTION;

    _settingSelected = 0;
    _joystickSelectedHeldTime = 0;

    _currentVolume = getAudioVolume();
    _currentWelcomeName = new char[EEPROM_WELCOME_NAME_SIZE + 1];
    _currentWelcomeName[EEPROM_WELCOME_NAME_SIZE] = '\0';
    readFromEEPROM(EEPROM_WELCOME_NAME_ADDRESS, _currentWelcomeName, EEPROM_WELCOME_NAME_SIZE);
    readFromEEPROM(EEPROM_MENU_THEME_ADDRESS, &_currentMenuTheme, 1);

    DrawScreenSettingSelection();
}

int GameSettings::Update_SettingSelection(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (joystickY < JOYSTICK_SELECT_BOUND_HIGH && joystickY > JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;
  }
  else if (joystickY >= JOYSTICK_SELECT_BOUND_HIGH) 
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _settingSelected = (_settingSelected + 1) % 3;
      playAudio(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenSettingSelection();
    }
  } 
  else
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _settingSelected = (_settingSelected - 1 + 3) % 3;
      playAudio(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenSettingSelection();
    }
  }    
}

int GameSettings::Update_Volume(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
    
}

int GameSettings::Update_Name(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
    
}

int GameSettings::Update_Theme(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
    
}

int GameSettings::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
    switch(gameState) 
    {
        case SETTING_SELECTION:
            return Update_SettingSelection(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
            break;
        case VOLUME:
            return Update_Volume(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
            break;
        case NAME:
            return Update_Name(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
            break;
        case THEME:
            return Update_Theme(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
            break;
    }
}

void GameSettings::DrawScreenSettingSelection() const
{
    tft.fillScreen(menuThemes[_currentMenuTheme].backgroundColor);

    switch(_settingSelected) 
    {
        case 0:
            drawWrappedText("Volum", 20, 25, 200, 100, 2, menuThemes[_currentMenuTheme].highlightColor);
            drawWrappedText("Colors menu", 20, 60, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);
            drawWrappedText("Nom usuari", 20, 95, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);

            tft.fillTriangle(12, 26, 16, 30, 12, 34, menuThemes[_currentMenuTheme].highlightColor);
            break;
        case 1:
            drawWrappedText("Volum", 20, 25, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);
            drawWrappedText("Colors menu", 20, 60, 200, 100, 2, menuThemes[_currentMenuTheme].highlightColor);
            drawWrappedText("Nom usuari", 20, 95, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);

            tft.fillTriangle(12, 62, 16, 66, 12, 70, menuThemes[_currentMenuTheme].highlightColor);
            break;
        case 2:
            drawWrappedText("Volum", 20, 25, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);
            drawWrappedText("Colors menu", 20, 60, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);
            drawWrappedText("Nom usuari", 20, 95, 200, 100, 2, menuThemes[_currentMenuTheme].highlightColor);

            tft.fillTriangle(12, 98, 16, 102, 12, 106, menuThemes[_currentMenuTheme].highlightColor);
            break;
    }
}

void GameSettings::DrawScreenVolume() const
{
    tft.fillScreen(menuThemes[_currentMenuTheme].backgroundColor);

    drawWrappedText("30", 70, 59, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);
    drawWrappedText("Prem per desar", 40, 110, 200, 100, 1, menuThemes[_currentMenuTheme].otherColor);

    tft.fillTriangle(80, 39, 85, 44, 75, 44, menuThemes[_currentMenuTheme].otherColor);
    tft.fillTriangle(80, 89, 85, 84, 75, 84, menuThemes[_currentMenuTheme].otherColor);
}