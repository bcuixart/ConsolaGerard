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

const PalettedBitmap* GameSettings::getIcon() const
{
  return &BITMAP_GAME_ICON_SETTINGS;
}

void GameSettings::Start()
{
    gameState = SETTING_SELECTION;

    _settingSelected = 0;
    _joystickSelectedHeldTime = 0;
    _currentWelcomeNameCharacter = 0;

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
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
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
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenSettingSelection();
    }
  }   
  
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) 
  {
     _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;

    if (_settingSelected == 0) 
    { 
      readFromEEPROM(EEPROM_VOLUME_ADDRESS, &_currentVolume, 1);
      setAudioVolume((int)_currentVolume);
      gameState = VOLUME; 
      DrawScreenVolume(); 
    }
    else if (_settingSelected == 1) 
    { 
      readFromEEPROM(EEPROM_MENU_THEME_ADDRESS, &_currentMenuTheme, 1);
      gameState = THEME; 
      DrawScreenTheme(); 
    }
    else if (_settingSelected == 2) 
    {
      readFromEEPROM(EEPROM_WELCOME_NAME_ADDRESS, _currentWelcomeName, EEPROM_WELCOME_NAME_SIZE); 
      gameState = NAME; 
      DrawScreenName(); 
    }
  }

  return 0;
}

int GameSettings::Update_Volume(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (joystickY < JOYSTICK_SELECT_BOUND_HIGH && joystickY > JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;
  }
  else if (joystickY <= JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      if (_currentVolume < 30)
      {
        _currentVolume = (_currentVolume + 1) % 31;
        setAudioVolume((int)_currentVolume);
        playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
        DrawScreenVolume();
      }
    }
  } 
  else
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      if (_currentVolume > 0) 
      {
        _currentVolume = (_currentVolume - 1 + 31) % 31;
        setAudioVolume((int)_currentVolume);
        playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
        DrawScreenVolume();
      }
    }
  }   
  
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) 
  {
     _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;
     writeToEEPROM(EEPROM_VOLUME_ADDRESS, &_currentVolume, 1);
     gameState = SETTING_SELECTION;
     DrawScreenSettingSelection();
  } 
  
  return 0;
}

int GameSettings::Update_Name(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  // Horizontal, select character
  // Vertical, change character
  if (joystickX < JOYSTICK_SELECT_BOUND_HIGH && joystickX > JOYSTICK_SELECT_BOUND_LOW && 
    joystickY < JOYSTICK_SELECT_BOUND_HIGH && joystickY > JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;
  }
  else if (joystickX <= JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _currentWelcomeNameCharacter = (_currentWelcomeNameCharacter - 1 + EEPROM_WELCOME_NAME_SIZE) % EEPROM_WELCOME_NAME_SIZE;
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenName();
    }
  } 
  else if (joystickX >= JOYSTICK_SELECT_BOUND_HIGH)
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _currentWelcomeNameCharacter = (_currentWelcomeNameCharacter + 1) % EEPROM_WELCOME_NAME_SIZE;
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenName();
    }
  }   
  else if (joystickY <= JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _currentWelcomeName[_currentWelcomeNameCharacter] = GetNextWelcomeNameCharacter(_currentWelcomeName[_currentWelcomeNameCharacter], false);
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenName();
    }
  } 
  else
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _currentWelcomeName[_currentWelcomeNameCharacter] = GetNextWelcomeNameCharacter(_currentWelcomeName[_currentWelcomeNameCharacter], true);
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenName();
    }
  }
  
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) 
  {
     _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;

     writeToEEPROM(EEPROM_WELCOME_NAME_ADDRESS, _currentWelcomeName, EEPROM_WELCOME_NAME_SIZE);
     gameState = SETTING_SELECTION;
     DrawScreenSettingSelection();
  }
  
  return 0;
}

int GameSettings::Update_Theme(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (joystickX < JOYSTICK_SELECT_BOUND_HIGH && joystickX > JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;
  }
  else if (joystickX <= JOYSTICK_SELECT_BOUND_LOW) 
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _currentMenuTheme = (_currentMenuTheme - 1 + MENU_THEME_COUNT) % MENU_THEME_COUNT;
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenTheme();
    }
  } 
  else
  {
    _joystickSelectedHeldTime += elapsed;
    if (_joystickSelectedHeldTime >= JOYSTICK_SELECT_HOLD_TIME) 
    {
      _joystickSelectedHeldTime = 0;
      _currentMenuTheme = (_currentMenuTheme + 1) % MENU_THEME_COUNT;
      playAudioMaxPriority(AUDIO_MENU_FOLDER, AUDIO_MENU_CHANGE_SELECTION);
      DrawScreenTheme();
    }
  }   
  
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) 
  {
     _joystickSelectedHeldTime = JOYSTICK_SELECT_HOLD_TIME;

     writeToEEPROM(EEPROM_MENU_THEME_ADDRESS, &_currentMenuTheme, 1);
     gameState = SETTING_SELECTION;
     DrawScreenSettingSelection();
  }   
  
  return 0;
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

    return 0;
}

char GameSettings::GetNextWelcomeNameCharacter(char currentChar, bool increment)
{
  int index = 0;
  while (index < WELCOME_NAME_CHARACTER_LIST_LENGTH && _welcomeNameCharacterList[index] != currentChar) ++index;

  if (index < WELCOME_NAME_CHARACTER_LIST_LENGTH) 
  {
    index = (index + (increment ? 1 : -1) + WELCOME_NAME_CHARACTER_LIST_LENGTH) % WELCOME_NAME_CHARACTER_LIST_LENGTH;
    return _welcomeNameCharacterList[index];
  }

  return 'A';
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

  char buff[4];
  sprintf(buff, "%d", _currentVolume);
  drawWrappedText(buff, 70, 59, 200, 100, 2, menuThemes[_currentMenuTheme].otherColor);
  drawWrappedText("Prem per desar", 40, 110, 200, 100, 1, menuThemes[_currentMenuTheme].otherColor);

  if (_currentVolume < 30) tft.fillTriangle(80, 39, 85, 44, 75, 44, menuThemes[_currentMenuTheme].otherColor);
  if (_currentVolume > 0) tft.fillTriangle(80, 89, 85, 84, 75, 84, menuThemes[_currentMenuTheme].otherColor);
}

void GameSettings::DrawScreenTheme() const
{
  tft.fillScreen(menuThemes[_currentMenuTheme].backgroundColor);

  for (int i = 0; i < MENU_THEME_COUNT; ++i) 
  {
    tft.fillRect(20 + 43 * i + 1, 49, 30, 30, menuThemes[i].backgroundColor);

    tft.fillRect(20 + 43 * i + 3, 51, 8, 8, menuThemes[i].otherColor);
    tft.fillRect(20 + 43 * i + 3, 60, 8, 8, menuThemes[i].highlightColor);
    tft.fillRect(20 + 43 * i + 3, 69, 8, 8, menuThemes[i].otherColor);

    drawWrappedText("Aa", 20 + 43 * i + 15, 60, 200, 100, 1, menuThemes[i].highlightColor);
  }
  tft.drawRect(20, 48, 32, 32, (_currentMenuTheme == 0) ? menuThemes[_currentMenuTheme].highlightColor : menuThemes[_currentMenuTheme].otherColor);
  tft.drawRect(63, 48, 32, 32, (_currentMenuTheme == 1) ? menuThemes[_currentMenuTheme].highlightColor : menuThemes[_currentMenuTheme].otherColor);
  tft.drawRect(106, 48, 32, 32, (_currentMenuTheme == 2) ? menuThemes[_currentMenuTheme].highlightColor : menuThemes[_currentMenuTheme].otherColor);

  tft.fillTriangle(20 + 43 * _currentMenuTheme + 11, 89, 20 + 43 * _currentMenuTheme + 16, 84, 20 + 43 * _currentMenuTheme + 21, 89, menuThemes[_currentMenuTheme].highlightColor);

  drawWrappedText("Prem per desar", 40, 110, 200, 100, 1, menuThemes[_currentMenuTheme].otherColor);
}

void GameSettings::DrawScreenName() const
{
  tft.fillScreen(menuThemes[_currentMenuTheme].backgroundColor);

  char buff[2] = {'A', '\0' };
  for (int i = 0; i < EEPROM_WELCOME_NAME_SIZE; ++i) 
  {
    //char buff[2] = { (char)(_currentWelcomeName[i]), '\0' };
    buff[0] = _currentWelcomeName[i];
    if (i == _currentWelcomeNameCharacter) {
      drawWrappedText(buff, 22 + 20 * i, 53, 200, 100, 3, menuThemes[_currentMenuTheme].highlightColor);

      tft.fillTriangle(29 + 20 * i, 39, 34 + 20 * i, 44, 24 + 20 * i, 44, menuThemes[_currentMenuTheme].highlightColor);
      tft.fillTriangle(29 + 20 * i, 89, 34 + 20 * i, 84, 24 + 20 * i, 84, menuThemes[_currentMenuTheme].highlightColor);
    }
    else drawWrappedText(buff, 22 + 20 * i, 53, 200, 100, 3, menuThemes[_currentMenuTheme].otherColor);
  }

  drawWrappedText("Prem per desar", 40, 110, 200, 100, 1, menuThemes[_currentMenuTheme].otherColor);
}