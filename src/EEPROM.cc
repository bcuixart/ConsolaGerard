#include "EEPROM.h"

void writeToEEPROM(int address, const void* data, size_t size)
{
    for (int i = 0; i < size; ++i) EEPROM.update(address + i, (uint8_t)((const uint8_t*)data)[i]);
}

void readFromEEPROM(int address, void* data, size_t size)
{
    for (int i = 0; i < size; ++i) ((uint8_t*)data)[i] = EEPROM.read(address + i);
}