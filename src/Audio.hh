#ifndef AUDIO_HH 
#define AUDIO_HH

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#define AUDIO_BUSY_PIN 7

#define AUDIO_FOLDER_BENVINGUT 1
#define AUDIO_FOLDER_BENVINGUT_NUM 6
#define AUDIO_FOLDER_MENU 2
#define AUDIO_FOLDER_MENU_CANVI_SELECCIO 1
#define AUDIO_FOLDER_GAME_AMONGUS 3
#define AUDIO_GAME_AMONGUS_ROUNDSTART 4
#define AUDIO_GAME_AMONGUS_REVEAL 1
#define AUDIO_GAME_AMONGUS_INCORRECT 2
#define AUDIO_GAME_AMONGUS_CORRECT 3
#define AUDIO_GAME_AMONGUS_GAMEOVER 5

extern DFRobotDFPlayerMini myDFPlayer;

bool initAudio(void);

//void printDetail(uint8_t type, int value);

void playAudio(int folder, int audio);

void playAudioRandomFolder(int folder, int folderNumAudios);

#endif
