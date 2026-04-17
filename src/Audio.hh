#ifndef AUDIO_HH 
#define AUDIO_HH

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#define AUDIO_BUSY_PIN 7

#define AUDIO_WELCOME_FOLDER 1
#define AUDIO_WELCOME_AUDIONUM 6
#define AUDIO_MENU_FOLDER 2
#define AUDIO_MENU_START 1
#define AUDIO_MENU_CHANGE_SELECTION 2
#define AUDIO_GAME_AMONGUS_FOLDER 3
#define AUDIO_GAME_AMONGUS_ROUNDSTART 4
#define AUDIO_GAME_AMONGUS_REVEAL 1
#define AUDIO_GAME_AMONGUS_INCORRECT 2
#define AUDIO_GAME_AMONGUS_CORRECT 3
#define AUDIO_GAME_AMONGUS_GAMEOVER 5
#define AUDIO_GAME_AMONGUS_TWERK 6

extern DFRobotDFPlayerMini myDFPlayer;

bool initAudio(void);

//void printDetail(uint8_t type, int value);

void playAudio(int folder, int audio);

void playAudioMaxPriority(int folder, int audio);

void playAudioRandomFolder(int folder, int folderNumAudios);

void stopAudio(void);

void setAudioVolume(int volume);
int getAudioVolume();

#endif
