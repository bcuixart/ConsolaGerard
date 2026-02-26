#include <Arduino.h>
#include "GameAmongUs.hh"
#include "GameSnake.hh"
#include "Menu.hh"
#include "Screen.hh"
#include "Audio.hh"

#define PIN_JOYSTICK_X A0
#define PIN_JOYSTICK_Y A1
#define PIN_JOYSTICK_B 4

#define JOYSTICK_HOLD_TO_MENU 5000
#define JOYSTICK_SHORT_PRESS_MAX 100

enum ConsoleState {
	MENU,
	GAME
};
ConsoleState state;

#define NUM_GAMES 7
Game* games[NUM_GAMES] = {
  new GameAmongUs(), // Amogus amagat sota tres copes 
  new GameSnake(),
  new Game(), // ARROW: Bloqueja fletxes girant el teu escut amb la palanca! Bloquejar fletxes a lo old man
  new Game(), // SPAMCLICK: Apreta la palanca tants cops com puguis en 10 segons!
  new Game(), // SPAMSPIN: Gira la palanca tants cops com puguis en 10 segons!
  new Game(), // REACTIONTIME: Apreata la palanca per disparar el teu rival!
  new Game(), // FOOTBALL: Gira la palanca per xutar pilotes i evitar que escapin!
};
unsigned char selectedGame = 0;

unsigned long oldMillis = 0;

unsigned long joystickHeldTime = 0;
unsigned long pressStartMillis = 0;
bool prevJoystickPressed = false;

void welcome(void);

void setup() 
{
  Serial.begin(9600);

  pinMode(PIN_JOYSTICK_X, INPUT);
  pinMode(PIN_JOYSTICK_Y, INPUT);
  pinMode(PIN_JOYSTICK_B, INPUT_PULLUP);

  initSceen();

  selectedGame = 0;

  joystickHeldTime = 0;
  
  oldMillis = millis();

  welcome();
}

void welcome()
{
  if (!initAudio())
    drawWrappedText("No s'ha pogut inicialitzar l'audio.", 16, 100, 128, 100, 1, ST7735_RED);

  drawWrappedText("Benvingut, Gerard!", 20, 44, 128, 100, 2, ST7735_WHITE);
  playAudioRandomFolder(AUDIO_WELCOME_FOLDER, AUDIO_WELCOME_AUDIONUM);

  delay(3000);

  oldMillis = millis();

  state = MENU;
  StartMenu(games, &selectedGame, NUM_GAMES);
}

void loop() 
{
  unsigned int joystickX = analogRead(PIN_JOYSTICK_X);
  unsigned int joystickY = analogRead(PIN_JOYSTICK_Y);
  bool joystickPressed = digitalRead(PIN_JOYSTICK_B) == LOW;

  unsigned long currentMillis = millis();
  unsigned long elapsed = currentMillis - oldMillis;

  // Start joystick press
  if (joystickPressed && !prevJoystickPressed) pressStartMillis = currentMillis;

  // End joystick press
  if (!joystickPressed && prevJoystickPressed) 
  {
    unsigned long pressDuration = currentMillis - pressStartMillis;
    if (state == MENU && pressDuration <= JOYSTICK_SHORT_PRESS_MAX) 
    {
      state = GAME;
      games[selectedGame]->Start();
    }
  }

  // Hold joystick press
  joystickHeldTime = joystickPressed ? (currentMillis - pressStartMillis) : 0;
  if (joystickHeldTime >= JOYSTICK_HOLD_TO_MENU && state == GAME) { state = MENU; StartMenu(games, &selectedGame, NUM_GAMES);}

  switch(state) 
  {
    case MENU:
    {
      if (!(joystickPressed && prevJoystickPressed == false)) UpdateMenu(joystickY, elapsed, &selectedGame, games, NUM_GAMES);
      break;
    }
    case GAME:
    {
      games[selectedGame]->Update(joystickX, joystickY, joystickPressed, joystickHeldTime, elapsed);
      break;
    }
  }

  prevJoystickPressed = joystickPressed;
  oldMillis = currentMillis;
}