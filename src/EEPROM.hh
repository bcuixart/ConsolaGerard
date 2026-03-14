#ifndef EEPROM_HH
#define EEPROM_HH

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_WELCOME_NAME_ADDRESS 0
#define EEPROM_WELCOME_NAME_SIZE 6
#define EEPROM_VOLUME_ADDRESS 10
#define EEPROM_MENU_THEME_ADDRESS 20

void writeToEEPROM(int address, const void* data, size_t size);
void readFromEEPROM(int address, void* data, size_t size);

#endif