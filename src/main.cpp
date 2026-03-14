#include <Arduino.h>
#include "GameAmongUs.hh"
#include "GameSnake.hh"
#include "GameSettings.hh"
#include "Menu.hh"
#include "Screen.hh"
#include "Audio.hh"

#define PIN_JOYSTICK_X A0
#define PIN_JOYSTICK_Y A1
#define PIN_JOYSTICK_B 4

#define JOYSTICK_HOLD_TO_MENU 5000
#define JOYSTICK_SHORT_PRESS_MAX 100
#define JOYSTICK_DEBOUNCE_MS 20

enum ConsoleState {
	MENU,
	GAME
};
ConsoleState state;

#define NUM_GAMES 8
Game* games[NUM_GAMES] = {
  new GameAmongUs(),
  new GameSnake(),
  new Game(), // ARROW: Bloqueja fletxes girant el teu escut amb la palanca! Bloquejar fletxes a lo old man
  new Game(), // SPAMCLICK: Apreta la palanca tants cops com puguis en 10 segons!
  new Game(), // SPAMSPIN: Gira la palanca tants cops com puguis en 10 segons!
  new Game(), // REACTIONTIME: Apreata la palanca per disparar el teu rival!
  new Game(), // FOOTBALL: Gira la palanca per xutar pilotes i evitar que escapin!
  new GameSettings(),
};
unsigned char selectedGame = 0;

unsigned long oldMillis = 0;

unsigned long joystickHeldTime = 0;
unsigned long pressStartMillis = 0;
bool prevJoystickPressed = false;
unsigned long lastDebounceMillis = 0;
bool lastRawJoystickPressed = false;
bool stableJoystickPressed = false;

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
  bool joystickPressedRaw = digitalRead(PIN_JOYSTICK_B) == LOW;

  unsigned long currentMillis = millis();
  unsigned long elapsed = currentMillis - oldMillis;

  // Debounce the joystick button: require stable state for JOYSTICK_DEBOUNCE_MS
  if (joystickPressedRaw != lastRawJoystickPressed) 
  {
    lastDebounceMillis = currentMillis;
    lastRawJoystickPressed = joystickPressedRaw;
  }

  if ((currentMillis - lastDebounceMillis) >= JOYSTICK_DEBOUNCE_MS) 
  {
    if (stableJoystickPressed != lastRawJoystickPressed) stableJoystickPressed = lastRawJoystickPressed;
  }

  // Start joystick press (based on debounced state)
  if (stableJoystickPressed && !prevJoystickPressed) pressStartMillis = currentMillis;

  // End joystick press (based on debounced state)
  if (!stableJoystickPressed && prevJoystickPressed) 
  {
    unsigned long pressDuration = currentMillis - pressStartMillis;
    if (state == MENU && pressDuration <= JOYSTICK_SHORT_PRESS_MAX) 
    {
      state = GAME;
      games[selectedGame]->Start();
      prevJoystickPressed = false; // treat as if the button is still pressed to prevent game logic from triggering on this release
    }
  }

  // Hold joystick press, don't reset hold time yet (use debounced state)
  if (stableJoystickPressed) {
    joystickHeldTime = (currentMillis - pressStartMillis);
    if (joystickHeldTime >= JOYSTICK_HOLD_TO_MENU && state == GAME) { state = MENU; StartMenu(games, &selectedGame, NUM_GAMES);}
  }

  switch(state) 
  {
    case MENU:
    {
      if (!(stableJoystickPressed && prevJoystickPressed == false)) UpdateMenu(joystickY, elapsed, &selectedGame, games, NUM_GAMES);
      break;
    }
    case GAME:
    {
      games[selectedGame]->Update(joystickX, joystickY, stableJoystickPressed, prevJoystickPressed, joystickHeldTime, elapsed);
      break;
    }
  }

  // Reset hold time if joystick is not pressed
  if (!stableJoystickPressed) joystickHeldTime = 0;

  prevJoystickPressed = stableJoystickPressed;
  oldMillis = currentMillis;
}