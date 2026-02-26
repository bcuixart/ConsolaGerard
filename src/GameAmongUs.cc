#include "api/Common.h"
#include "GameAmongUs.hh"

GameAmongUs::GameAmongUs()
{

}

void GameAmongUs::Start()
{
  gameState = START;

  correctCup = 0;
  selectedCup = 0;
  hasChangedSelectedJoystick = false;
  
  tft.fillRect(0, 0, 160, 73, COLOR_WALL);
  tft.fillRect(0, 73, 160, 55, COLOR_FLOOR);

  drawAlphaBitmap(5,37,BITMAP_GAME_AMONGUS_CUP,49,49);
  drawAlphaBitmap(55,37,BITMAP_GAME_AMONGUS_CUP,49,49);
  drawAlphaBitmap(105,37,BITMAP_GAME_AMONGUS_CUP,49,49);
}

const char* GameAmongUs::getNom() const
{
  return _nom;
}

const char* GameAmongUs::getDesc() const
{
  return _desc;
}

const uint16_t* GameAmongUs::getIcon() const
{
  return BITMAP_GAME_ICON_AMONGUS;
}

void GameAmongUs::Update_Start(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (joystickPressed && joystickHeldTime <= 100) gameState = ROUNDTITLE;
}

void GameAmongUs::Update_RoundTitle(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  playAudio(AUDIO_FOLDER_GAME_AMONGUS, AUDIO_GAME_AMONGUS_ROUNDSTART);

  tft.fillRect(5 + correctCup * 50, 37, 49, 36, COLOR_WALL);
  tft.fillRect(5 + correctCup * 50, 73, 49, 13, COLOR_FLOOR);
  drawAlphaBitmap(5 + correctCup * 50, 0, BITMAP_GAME_AMONGUS_CUP, 49, 49);

  drawAlphaBitmap(13 + correctCup * 50, 42, BITMAP_GAME_AMONGUS_AMONGUS, 34, 44);

  delay(3000);

  tft.fillRect(5 + correctCup * 50, 0, 49, 49, COLOR_WALL);
  drawAlphaBitmap(5 + correctCup * 50, 37, BITMAP_GAME_AMONGUS_CUP, 49, 49);

  gameState = ROUNDMOVEMENT;
}

void GameAmongUs::Update_RoundMovement(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  int numMovements = 5;
  int delayTime = 1;
  for (int m = 0; m < numMovements; ++m) 
  {
    int movement = random(0, 2); // 0 o 1

    // Canvien de lloc la del mig i l'esquerra
    if (movement == 0)
    {
      if (correctCup == 0) correctCup = 1;
      else if (correctCup == 1) correctCup = 0;

      tft.fillRect(5, 37, 55 + 49 - 5, 36, COLOR_WALL);
      tft.fillRect(5, 73, 55 + 49 - 5, 13, COLOR_FLOOR);
      drawAlphaBitmap(25,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      tft.fillRect(25, 37, 49, 36, COLOR_WALL);
      tft.fillRect(25, 73, 49, 13, COLOR_FLOOR);
      drawAlphaBitmap(5,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      drawAlphaBitmap(55,37,BITMAP_GAME_AMONGUS_CUP,49,49);

      /*
      for (int s = 0; s <= 50; s += 25) 
      {
        int cupPosXLeft = 5 + s;
        int cupPosXRight = 55 - s;

        tft.fillRect(5, 37, 55 + 49 - 5, 36, COLOR_WALL);
        tft.fillRect(5, 73, 55 + 49 - 5, 13, COLOR_FLOOR);
        drawAlphaBitmap(cupPosXLeft,37,BITMAP_GAME_AMONGUS_CUP,49,49);
        //drawAlphaBitmap(cupPosXRight,37,BITMAP_GAME_AMONGUS_CUP,49,49);

        //delay(delayTime);
      }
      */
    }
    // Canvien de lloc la del mig i la dreta
    else 
    {
      if (correctCup == 2) correctCup = 1;
      else if (correctCup == 1) correctCup = 2;

      tft.fillRect(55, 37, 55 + 49 - 5, 36, COLOR_WALL);
      tft.fillRect(55, 73, 55 + 49 - 5, 13, COLOR_FLOOR);
      drawAlphaBitmap(75,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      tft.fillRect(75, 37, 49, 36, COLOR_WALL);
      tft.fillRect(75, 73, 49, 13, COLOR_FLOOR);
      drawAlphaBitmap(55,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      drawAlphaBitmap(105,37,BITMAP_GAME_AMONGUS_CUP,49,49);

      /*
      for (int s = 0; s <= 50; s += 25) 
      {
        int cupPosXLeft = 55 + s;
        int cupPosXRight = 105 - s;

        tft.fillRect(55, 37, 105 + 49 - 55, 36, COLOR_WALL);
        tft.fillRect(55, 73, 105 + 49 - 55, 13, COLOR_FLOOR);
        drawAlphaBitmap(cupPosXLeft,37,BITMAP_GAME_AMONGUS_CUP,49,49);
        //drawAlphaBitmap(cupPosXRight,37,BITMAP_GAME_AMONGUS_CUP,49,49);

        //delay(delayTime);
      }
      */
    }
  }
  
  selectedCup = 0;
  drawAlphaBitmap((160/4) * (selectedCup+1) - 12, 128-42, BITMAP_GAME_AMONGUS_HAND,25,42);

  gameState = CHOOSING;
}

void GameAmongUs::Update_Choosing(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  char selectedOld = selectedCup;
  if (joystickX < JOYSTICK_SELECT_BOUND_HIGH && joystickX > JOYSTICK_SELECT_BOUND_LOW) 
  {
    hasChangedSelectedJoystick = false;
  }
  else if (!hasChangedSelectedJoystick && joystickX >= JOYSTICK_SELECT_BOUND_HIGH) 
  {
    hasChangedSelectedJoystick = true;
    selectedCup = (selectedCup + 1) % 3;
  } 
  else if (!hasChangedSelectedJoystick && joystickX <= JOYSTICK_SELECT_BOUND_LOW)
  {
    hasChangedSelectedJoystick = true;
    selectedCup = (selectedCup + 2) % 3;
  }

  if (selectedOld != selectedCup) 
  {
    tft.fillRect((160/4) * (selectedOld+1) - 12, 128-42, 25, 42, COLOR_FLOOR);
    drawAlphaBitmap((160/4) * (selectedCup+1) - 12, 128-42, BITMAP_GAME_AMONGUS_HAND,25,42);
  }

  if (joystickPressed && joystickHeldTime <= 100) 
  {
    playAudio(AUDIO_FOLDER_GAME_AMONGUS, AUDIO_GAME_AMONGUS_REVEAL);
    gameState = REVEAL;
  }
}

void GameAmongUs::Update_Reveal(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  tft.fillRect((160/4) * (selectedCup+1) - 12, 128-42, 25, 42, COLOR_FLOOR);

  delay(4000);

  tft.fillRect(5 + selectedCup * 50, 37, 49, 36, COLOR_WALL);
  tft.fillRect(5 + selectedCup * 50, 73, 49, 13, COLOR_FLOOR);
  drawAlphaBitmap(5 + selectedCup * 50, 0, BITMAP_GAME_AMONGUS_CUP, 49, 49);

  if (selectedCup == correctCup) 
  {
    drawAlphaBitmap(13 + correctCup * 50, 42, BITMAP_GAME_AMONGUS_AMONGUS, 34, 44);

    playAudio(AUDIO_FOLDER_GAME_AMONGUS, AUDIO_GAME_AMONGUS_CORRECT);

    delay(2000);

    gameState = ROUNDTITLE;
  }
  else 
  { 
    playAudio(AUDIO_FOLDER_GAME_AMONGUS, AUDIO_GAME_AMONGUS_INCORRECT);

    delay(2000);
    
    tft.fillRect(5 + correctCup * 50, 37, 49, 36, COLOR_WALL);
    tft.fillRect(5 + correctCup * 50, 73, 49, 13, COLOR_FLOOR);
    drawAlphaBitmap(5 + correctCup * 50, 0, BITMAP_GAME_AMONGUS_CUP, 49, 49);

    drawAlphaBitmap(13 + correctCup * 50, 42, BITMAP_GAME_AMONGUS_AMONGUS, 34, 44);

    playAudio(AUDIO_FOLDER_GAME_AMONGUS, AUDIO_GAME_AMONGUS_GAMEOVER);

    delay(5000);

    Start();
  }
}

int GameAmongUs::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  switch(gameState) 
  {
    case START: {
      Update_Start(joystickX, joystickY, joystickPressed, joystickHeldTime, elapsed);
      break;
    }
    case ROUNDTITLE: {
      Update_RoundTitle(joystickX, joystickY, joystickPressed, joystickHeldTime, elapsed);
      break;
    }
    case ROUNDMOVEMENT: {
      Update_RoundMovement(joystickX, joystickY, joystickPressed, joystickHeldTime, elapsed);
      break;
    }
    case CHOOSING: {
      Update_Choosing(joystickX, joystickY, joystickPressed, joystickHeldTime, elapsed);
      break;
    }
    case REVEAL: {
      Update_Reveal(joystickX, joystickY, joystickPressed,joystickHeldTime, elapsed);
      break;
    }
  }
  return 0;
}