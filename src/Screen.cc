#include "Screen.hh"

/* CONNEXIO:
GND -> GND
VCC -> 3.3V
SCL -> (RES) -> 13 (GROC)
SDA -> (RES) -> 11 (VERD)
RES -> RES -> 9 (BLAU)
DC -> RES -> 8 (LILA)
CS -> RES -> 10 (GRIS)
BL -> 3.3V
*/
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initSceen(void) 
{
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  // OR use this initializer if using a 1.8" TFT screen with offset such as WaveShare:
  //tft.initR(INITR_GREENTAB);      // Init ST7735S chip, green tab

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  //tft.setSPISpeed(40000000);

  tft.setRotation(1);

  tft.fillScreen(ST77XX_BLACK);
}

void drawWrappedText(const char* text, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t s, uint16_t c) 
{
    tft.setCursor(x, y);
    tft.setTextWrap(true);
    tft.setTextSize(s);
    tft.setTextColor(c);

    int16_t cursorX = x;
    int16_t cursorY = y;
    
    while (*text) 
    {
        int16_t tx, ty;
        uint16_t tw, th;
        char charBuf[2] = {*text, '\0'};
        tft.getTextBounds(charBuf, cursorX, cursorY, &tx, &ty, &tw, &th);

        if (cursorX + tw > x + w) {
            cursorX = x;
            cursorY += th + 2;
            
            if (cursorY > y + h - th) return;

            tft.setCursor(cursorX, cursorY);
        }

        tft.print(*text);
        cursorX += tw;
        text++;
    }
}

void drawAlphaBitmap(int x, int y, const uint16_t* bitmap, int w, int h)
{
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            uint16_t color = pgm_read_word(&bitmap[j * w + i]);
            if (color != ALPHA_COLOR) {
                tft.drawPixel(x + i, y + j, color);
            }
        }
    } 
}

void drawPaletteBitmap(int x, int y, const PalettedBitmap& bitmap)
{
    uint16_t* bitmap_to_draw = (uint16_t*)malloc(bitmap.width * bitmap.height * sizeof(uint16_t));
    uint16_t *bitmap_pointer = bitmap_to_draw;

    uint16_t data_size = bitmap.data_size;
    for (int i = 0; i < data_size; ++i) 
    {
        uint8_t byte = bitmap.data[i];
        uint8_t palette_index = byte >> 4;
        uint8_t pixel_count = byte & 0x0F;

        for (int j = 0; j < pixel_count + 1; ++j) 
        {
            *bitmap_pointer++ = bitmap.palette[palette_index];
        }
    }

    tft.drawRGBBitmap(x, y, bitmap_to_draw, bitmap.width, bitmap.height);
    if (bitmap_to_draw) free(bitmap_to_draw);
}