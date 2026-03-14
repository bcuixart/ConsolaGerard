#include "GameSettings.hh"

GameSettings::GameSettings()
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

    tft.fillScreen(ST77XX_WHITE);

    _currentVolume = getAudioVolume();
    _currentWelcomeName = new char[EEPROM_WELCOME_NAME_SIZE + 1];
    _currentWelcomeName[EEPROM_WELCOME_NAME_SIZE] = '\0';
    readFromEEPROM(EEPROM_WELCOME_NAME_ADDRESS, _currentWelcomeName, EEPROM_WELCOME_NAME_SIZE);
    readFromEEPROM(EEPROM_MENU_THEME_ADDRESS, &_currentMenuTheme, 1);
}

int GameSettings::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
    
}
