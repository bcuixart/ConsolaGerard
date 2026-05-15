#ifndef SCREEN_HH 
#define SCREEN_HH

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include "Bitmaps.hh"

#define TFT_CS        10
#define TFT_RST        9
#define TFT_DC         8

#define ALPHA_COLOR 0xf81f

// For 1.44" and 1.8" TFT with ST7735 use:
extern Adafruit_ST7735 tft;

void initSceen(void);

void drawWrappedText(const char* text, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t s, uint16_t c);

void drawAlphaBitmap(int x, int y, const uint16_t* bitmap, int w, int h);

void drawPaletteBitmap(int x, int y, const PalettedBitmap& bitmap);

#endif
