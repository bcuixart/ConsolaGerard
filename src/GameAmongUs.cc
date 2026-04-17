#include "api/Common.h"
#include "GameAmongUs.hh"

GameAmongUs::GameAmongUs()
{

}

void GameAmongUs::Start()
{
  gameState = START;

  waitDuration = 0;
  stateElapsed = 0;

  round = 1;

  correctCup = 0;
  selectedCup = 0;
  hasChangedSelectedJoystick = false;
  
  amongUsTwerkPosition = -45;

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

void GameAmongUs::Update_Start(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) gameState = ROUNDTITLE;
}

void GameAmongUs::Update_RoundTitle(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (waitDuration == 0) 
  {
    playAudio(AUDIO_GAME_AMONGUS_FOLDER, AUDIO_GAME_AMONGUS_ROUNDSTART);

    tft.fillRect(5 + correctCup * 50, 37, 49, 36, COLOR_WALL);
    tft.fillRect(5 + correctCup * 50, 73, 49, 13, COLOR_FLOOR);
    drawAlphaBitmap(5 + correctCup * 50, 0, BITMAP_GAME_AMONGUS_CUP, 49, 49);

    drawAlphaBitmap(13 + correctCup * 50, 42, BITMAP_GAME_AMONGUS_AMONGUS, 34, 44);

    tft.fillRect(0, 89, 160, 39, COLOR_FLOOR);
    drawWrappedText(("Ronda " + String(round)).c_str(), 10, 100, 140, 20, 2, COLOR_WALL);

    waitDuration = 3000;
    stateElapsed = 0;
    return;
  }

  stateElapsed += elapsed;
  if (stateElapsed >= waitDuration) 
  {
    tft.fillRect(5 + correctCup * 50, 0, 49, 49, COLOR_WALL);
    drawAlphaBitmap(5 + correctCup * 50, 37, BITMAP_GAME_AMONGUS_CUP, 49, 49);

    tft.fillRect(0, 89, 160, 39, COLOR_FLOOR);

    waitDuration = 0;
    stateElapsed = 0;

    roundNumMovements = 3 + (round - 1);
    roundMovement = random(0, 2);
    roundMovementDuration = (1.0f - (round - 1) * 0.1f) * 1000;
    roundMovementDuration = max(roundMovementDuration, 100);
    roundTotalDuration = roundMovementDuration * roundNumMovements;
    roundTotalElapsed = 0;
    amongUsTwerkFrame = 0;
    roundReachedHalfway = false;

    thisRoundHasTwerk = round >= 5 && random(0, 2) == 0;
    amongUsTwerkPosition = -45;

    if (thisRoundHasTwerk) playAudioMaxPriority(AUDIO_GAME_AMONGUS_FOLDER, AUDIO_GAME_AMONGUS_TWERK);
    gameState = ROUNDMOVEMENT;
  }
}

void GameAmongUs::Update_RoundMovement(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (stateElapsed == 0)
  {
    if (roundMovement == 0) // Canvien de lloc la del mig i l'esquerra
    {
      if (correctCup == 0) correctCup = 1;
      else if (correctCup == 1) correctCup = 0;

      tft.fillRect(5, 37, 55 + 49 - 5, 36, COLOR_WALL);
      tft.fillRect(5, 73, 55 + 49 - 5, 13, COLOR_FLOOR);
      drawAlphaBitmap(25,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      //tft.drawFastHLine(15, 50, 89, ST77XX_BLUE);
      //tft.drawFastHLine(15, 70, 89, ST77XX_BLUE);
    }
    else // Canvien de lloc la del mig i la dreta
    {
      if (correctCup == 2) correctCup = 1;
      else if (correctCup == 1) correctCup = 2;

      tft.fillRect(55, 37, 55 + 49 - 5, 36, COLOR_WALL);
      tft.fillRect(55, 73, 55 + 49 - 5, 13, COLOR_FLOOR);
      drawAlphaBitmap(75,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      //tft.drawFastHLine(55, 50, 89, ST77XX_BLUE);
      //tft.drawFastHLine(55, 70, 89, ST77XX_BLUE);
    }
  }

  stateElapsed += elapsed;
  roundTotalElapsed += elapsed;

  if (thisRoundHasTwerk)
  {
    amongUsTwerkFrame += 0.2f;
    amongUsTwerkPosition = -45.0f + ((float)roundTotalElapsed / roundTotalDuration) * (173.0f - -45.0f);
    DrawAmongusTwerk();
  }

  if (stateElapsed >= roundMovementDuration / 2 && !roundReachedHalfway) 
  {
    roundReachedHalfway = true;
    if (roundMovement == 0) // Canvien de lloc la del mig i l'esquerra
    {
      tft.fillRect(25, 37, 49, 36, COLOR_WALL);
      tft.fillRect(25, 73, 49, 13, COLOR_FLOOR);
      drawAlphaBitmap(5,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      drawAlphaBitmap(55,37,BITMAP_GAME_AMONGUS_CUP,49,49);
    }
    else // Canvien de lloc la del mig i la dreta
    {
      tft.fillRect(75, 37, 49, 36, COLOR_WALL);
      tft.fillRect(75, 73, 49, 13, COLOR_FLOOR);
      drawAlphaBitmap(55,37,BITMAP_GAME_AMONGUS_CUP,49,49);
      drawAlphaBitmap(105,37,BITMAP_GAME_AMONGUS_CUP,49,49);
    }
  }

  if (stateElapsed >= roundMovementDuration) 
  {
    stateElapsed = 0;
    roundNumMovements--;

    roundReachedHalfway = false;
    roundMovement = random(0, 2);

    if (roundNumMovements <= 0) 
    {
      selectedCup = 0;
      drawAlphaBitmap(18+50*selectedCup, 128-42, BITMAP_GAME_AMONGUS_HAND,25,42);

      stopAudio();

      gameState = CHOOSING;
      return;
    }
  }
}

void GameAmongUs::Update_Choosing(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
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
    tft.fillRect(18+50*selectedOld, 128-42, 25, 42, COLOR_FLOOR);
    drawAlphaBitmap(18+50*selectedCup, 128-42, BITMAP_GAME_AMONGUS_HAND,25,42);
  }

  if (!joystickPressed && prevJoystickPressed && joystickHeldTime <= JOYSTICK_SHORT_PRESS_MAX) 
  {
    playAudio(AUDIO_GAME_AMONGUS_FOLDER, AUDIO_GAME_AMONGUS_REVEAL);
    gameState = REVEAL;
  }
}

void GameAmongUs::Update_Reveal(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  if (waitDuration == 0) 
  {
    tft.fillRect(18+50*selectedCup, 128-42, 25, 42, COLOR_FLOOR);
    waitDuration = 4000;
    stateElapsed = 0;
    return;
  }

  stateElapsed += elapsed;

  if (stateElapsed >= waitDuration) 
  {
    tft.fillRect(5 + selectedCup * 50, 37, 49, 36, COLOR_WALL);
    tft.fillRect(5 + selectedCup * 50, 73, 49, 13, COLOR_FLOOR);
    drawAlphaBitmap(5 + selectedCup * 50, 0, BITMAP_GAME_AMONGUS_CUP, 49, 49);

    stateElapsed = 0;
    if (selectedCup == correctCup) 
    {
      drawAlphaBitmap(13 + correctCup * 50, 42, BITMAP_GAME_AMONGUS_AMONGUS, 34, 44);
      playAudio(AUDIO_GAME_AMONGUS_FOLDER, AUDIO_GAME_AMONGUS_CORRECT);
      waitDuration = 2000;
      gameState = REVEAL_CORRECT;
    } 
    else 
    {
      playAudio(AUDIO_GAME_AMONGUS_FOLDER, AUDIO_GAME_AMONGUS_INCORRECT);
      waitDuration = 2000;
      gameState = REVEAL_INCORRECT;
    }
  }
}

void GameAmongUs::Update_RevealCorrect(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  stateElapsed += elapsed;
  if (stateElapsed >= waitDuration) 
  {
    stateElapsed = 0;
    waitDuration = 0;
    gameState = ROUNDTITLE;

    ++round;
    return;
  }
}

void GameAmongUs::Update_RevealIncorrect(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  stateElapsed += elapsed;
  if (stateElapsed >= waitDuration && waitDuration == 2000) 
  {
    stateElapsed = 0;
    tft.fillRect(5 + correctCup * 50, 37, 49, 36, COLOR_WALL);
    tft.fillRect(5 + correctCup * 50, 73, 49, 13, COLOR_FLOOR);
    drawAlphaBitmap(5 + correctCup * 50, 0, BITMAP_GAME_AMONGUS_CUP, 49, 49);

    drawAlphaBitmap(13 + correctCup * 50, 42, BITMAP_GAME_AMONGUS_AMONGUS, 34, 44);
    playAudio(AUDIO_GAME_AMONGUS_FOLDER, AUDIO_GAME_AMONGUS_GAMEOVER);
    waitDuration = 5000;
    return;
  }

  if (stateElapsed >= waitDuration && waitDuration == 5000) 
  {
    stateElapsed = 0;
    waitDuration = 0;
    Start();
    return;
  }
}

void GameAmongUs::DrawAmongusTwerk()
{
  if ((int)amongUsTwerkLastDrawnPosition != (int)amongUsTwerkPosition)
  {
    tft.fillRect((int)amongUsTwerkLastDrawnPosition, 89, (int)amongUsTwerkPosition - (int)amongUsTwerkLastDrawnPosition, 43, COLOR_FLOOR);
    tft.drawRGBBitmap((int)amongUsTwerkPosition, 89, int(amongUsTwerkFrame) % 2 == 0 ? BITMAP_GAME_AMONGUS_TWERK_001 : BITMAP_GAME_AMONGUS_TWERK_002, 43, 43);
    amongUsTwerkLastDrawnPosition = amongUsTwerkPosition;
  }
}

int GameAmongUs::Update(unsigned int joystickX, unsigned int joystickY, bool joystickPressed, bool prevJoystickPressed, unsigned long joystickHeldTime, unsigned long elapsed)
{
  switch(gameState) 
  {
    case START: 
      Update_Start(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case ROUNDTITLE: 
      Update_RoundTitle(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case ROUNDMOVEMENT: 
      Update_RoundMovement(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case CHOOSING: 
      Update_Choosing(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case REVEAL:
      Update_Reveal(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case REVEAL_CORRECT:
      Update_RevealCorrect(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    case REVEAL_INCORRECT:
      Update_RevealIncorrect(joystickX, joystickY, joystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
  }
  return 0;
}