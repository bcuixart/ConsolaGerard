#include "Audio.hh"

/* FORMAT EXPORTAR AUDIO
FORMAT: MP3
SAMPLE RATE: 44100 Hz
BIT RATE MODE: CONSTANT
QUALITY: 192 KBPS
NO TRIM BLANK SPACE BEFORE FIRST CLIP
*/


/* CONNEXIO
(ESQUERRA TARGETA MIRANT ABAIX)
VCC -> 5V
RX -> RES -> TX ARDUINO (1)
TX -> RX ARDUINO (0)
-
-
SPEAKER NEGRE
GND -> GND
SPEAKER VERMELL

(DRETA)
BUSY -> ARDUINO 7

*/

bool audioInitializedCorrectly = false;

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;

bool initAudio()
{
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  FPSerial.begin(9600);
#endif

  pinMode(AUDIO_BUSY_PIN, INPUT);

  int attempts = 5;
  audioInitializedCorrectly = false;
  while (attempts > 0)
  {
    if (myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {
      audioInitializedCorrectly = true;
      break;
    }
    --attempts;
    delay(100);
  }  

  if (!audioInitializedCorrectly) { 
    Serial.println(F("Unable to begin audio."));
  }
  else {
    Serial.print("Audio successfully started. Attemps: ");
    Serial.println(6 - attempts);
  }
  
  setAudioVolume(30);

  return audioInitializedCorrectly;
}

void playAudio(int folder, int audio)
{
  if (!audioInitializedCorrectly) return;

  if (digitalRead(AUDIO_BUSY_PIN)) myDFPlayer.playFolder(folder, audio);
}

void playAudioMaxPriority(int folder, int audio)
{
  if (!audioInitializedCorrectly) return;

  myDFPlayer.playFolder(folder, audio); 
}

void playAudioRandomFolder(int folder, int folderNumAudios)
{
  playAudio(folder, random(1, folderNumAudios + 1));
}

void stopAudio(void)
{
  if (!audioInitializedCorrectly) return;

  myDFPlayer.stop();
}

void setAudioVolume(int volume)
{
  if (!audioInitializedCorrectly) return;
  
  if (volume < 0) volume = 0;
  if (volume > 30) volume = 30;

  myDFPlayer.volume(volume);
}

int getAudioVolume()
{
  if (!audioInitializedCorrectly) return 0;
  
  return myDFPlayer.readVolume();
}

/*
void printDetail(uint8_t type, int value)
{
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
*/